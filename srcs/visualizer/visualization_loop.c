/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization_loop.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 16:09:33 by smorty            #+#    #+#             */
/*   Updated: 2019/08/26 23:35:02 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler_visualizer.h"

static void	print_board(char **board)
{
	while (*board)
	{
		ft_putstr(*board++);
		write(1, "\n", 1);
	}
	write(1, "\n", 1);
}

static void	change_colors(t_filler_vis *game, int color_num)
{
	if (color_num == 1)
	{
		game->p1_color->r = (O_COLOR_1 >> 16) & 0xff;
		game->p1_color->g = (O_COLOR_1 >> 8) & 0xff;
		game->p1_color->b = O_COLOR_1 & 0xff;
		game->p2_color->r = (X_COLOR_1 >> 16) & 0xff;
		game->p2_color->g = (X_COLOR_1 >> 8) & 0xff;
		game->p2_color->b = X_COLOR_1 & 0xff;
	}
	else if (color_num == 2)
	{
		game->p1_color->r = (O_COLOR_2 >> 16) & 0xff;
		game->p1_color->g = (O_COLOR_2 >> 8) & 0xff;
		game->p1_color->b = O_COLOR_2 & 0xff;
		game->p2_color->r = (X_COLOR_2 >> 16) & 0xff;
		game->p2_color->g = (X_COLOR_2 >> 8) & 0xff;
		game->p2_color->b = X_COLOR_2 & 0xff;
	}
	else
	{
		game->p1_color->r = (O_COLOR_DEF >> 16) & 0xff;
		game->p1_color->g = (O_COLOR_DEF >> 8) & 0xff;
		game->p1_color->b = O_COLOR_DEF & 0xff;
		game->p2_color->r = (X_COLOR_DEF >> 16) & 0xff;
		game->p2_color->g = (X_COLOR_DEF >> 8) & 0xff;
		game->p2_color->b = X_COLOR_DEF & 0xff;
	}
}

static void	key_handler(SDL_Event *e, t_filler_vis *game, t_vis_status *status)
{
	if (e->key.keysym.sym == SDLK_ESCAPE)
		status->quit = 1;
	else if (e->key.keysym.sym == SDLK_SPACE)
		status->pause = ~status->pause;
	else if (e->key.keysym.sym == SDLK_KP_PLUS && status->speed)
		--status->speed;
	else if (e->key.keysym.sym == SDLK_KP_MINUS && status->speed < 100)
		++status->speed;
	else if (e->key.keysym.sym == SDLK_LEFT && status->pause && game->board_states->left)
	{
		game->board_states = game->board_states->left;
		if (status->print)
			print_board(game->board_states->board);
	}
	else if (e->key.keysym.sym == SDLK_RIGHT && status->pause && game->board_states->right)
	{
		game->board_states = game->board_states->right;
		if (status->print)
			print_board(game->board_states->board);
	}
	else if (e->key.keysym.sym == SDLK_KP_ENTER)
		status->print = ~status->print;
	else if (e->key.keysym.sym == SDLK_TAB)
		status->controls = ~status->controls;
	else if (e->key.keysym.sym == SDLK_BACKSPACE)
	{
		if (++status->color == 3)
			status->color = 0;
		change_colors(game, status->color);
	}
}

static void	init_status(t_vis_status *status)
{
	status->quit = 0;
	status->pause = 0;
	status->ended = 0;
	status->speed = 0;
	status->print = 0;
	status->controls = 0;
	status->color = 0;
}

void		visualization_loop(t_filler_vis *game)
{
	SDL_Event		e;
	t_vis_status	status;
	int				speed_counter;

	init_status(&status);
	speed_counter = 0;
	while (!status.quit)
	{
		if (speed_counter)
			--speed_counter;
		if (!status.ended)
			get_next_board(game, game->height);
		visualize(game, status.controls);
		if (game->board_states->last)
		{
			status.ended = -1;
			status.pause = -1;
		}
		if (!status.pause && !status.controls && !speed_counter && game->board_states->right)
		{
			game->board_states = game->board_states->right;
			if (status.print)
				print_board(game->board_states->board);
			speed_counter = status.speed;
		}
		if (SDL_PollEvent(&e) && e.type == SDL_KEYDOWN)
			key_handler(&e, game, &status);
	}
}
