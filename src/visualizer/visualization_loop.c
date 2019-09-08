/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization_loop.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 16:09:33 by smorty            #+#    #+#             */
/*   Updated: 2019/08/28 23:24:55 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler_visualizer.h"

static int	next_board(t_filler_vis *game, t_vis_status *status, const int dir)
{
	t_board	*next;
	char	**board;

	next = dir ? game->board_states->right : game->board_states->left;
	if (next)
	{
		if (status->print)
		{
			board = next->board;
			while (*board)
				ft_putendl(*board++);
			write(1, "\n", 1);
		}
		if (next->last)
		{
			status->ended = -1;
			status->pause = -1;
		}
		game->board_states = next;
	}
	return (status->speed);
}

static void	change_colors(t_filler_vis *game, const int color_num)
{
	int color1[8];
	int color2[8];

	color1[0] = O_COLOR_DEF;
	color2[0] = X_COLOR_DEF;
	color1[1] = O_COLOR_1;
	color2[1] = X_COLOR_1;
	color1[2] = O_COLOR_2;
	color2[2] = X_COLOR_2;
	color1[3] = O_COLOR_3;
	color2[3] = X_COLOR_3;
	color1[4] = O_COLOR_4;
	color2[4] = X_COLOR_4;
	color1[5] = O_COLOR_5;
	color2[5] = X_COLOR_5;
	color1[6] = O_COLOR_6;
	color2[6] = X_COLOR_6;
	color1[7] = O_COLOR_7;
	color2[7] = X_COLOR_7;
	game->p1_color->r = (color1[color_num] >> 16) & 0xff;
	game->p1_color->g = (color1[color_num] >> 8) & 0xff;
	game->p1_color->b = color1[color_num] & 0xff;
	game->p2_color->r = (color2[color_num] >> 16) & 0xff;
	game->p2_color->g = (color2[color_num] >> 8) & 0xff;
	game->p2_color->b = color2[color_num] & 0xff;
}

static void	key_press(t_filler_vis *game, t_vis_status *status, SDL_Keycode key)
{
	if (key == SDLK_SPACE)
		status->pause = ~status->pause;
	else if (key == SDLK_KP_PLUS && status->speed)
		--status->speed;
	else if (key == SDLK_KP_MINUS && status->speed < 100)
		++status->speed;
	else if (key == SDLK_KP_ENTER)
		status->print = ~status->print;
	else if (key == SDLK_TAB)
		status->controls = ~status->controls;
	else if (key == SDLK_LEFT && status->pause)
		next_board(game, status, 0);
	else if (key == SDLK_RIGHT && status->pause)
		next_board(game, status, 1);
	else if (key == SDLK_BACKSPACE)
		change_colors(game, (status->color += (status->color < 8 ? 1 : -8)));
	else if (key == SDLK_ESCAPE)
		status->quit = 1;
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
	int				delay;

	init_status(&status);
	delay = 0;
	while (!status.quit)
	{
		if (!status.ended)
			get_next_board(game, game->height);
		visualize(game, status.controls);
		if (!status.pause && !status.controls)
			delay += (delay ? -1 : next_board(game, &status, 1));
		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN)
				key_press(game, &status, e.key.keysym.sym);
			if (e.type == SDL_WINDOWEVENT
				&& e.window.event == SDL_WINDOWEVENT_CLOSE)
				status.quit = 1;
		}
	}
}
