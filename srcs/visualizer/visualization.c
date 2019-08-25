/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 16:09:33 by smorty            #+#    #+#             */
/*   Updated: 2019/08/25 23:11:51 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler_visualizer.h"

SDL_Rect			*get_rectangle(int x, int y, int width, int height)
{
	SDL_Rect *rect;

	if (!(rect = (SDL_Rect *)malloc(sizeof(SDL_Rect))))
		error(strerror(errno));
	rect->x = x;
	rect->y = y;
	rect->w = width;
	rect->h = height;
	return (rect);
}

static void			set_color(SDL_Renderer *renderer, t_filler_vis *game, char type)
{
	SDL_Color color;

	color.a = 0;
	if (type == 'O')
	{
		color.r = game->p1_color->r;
		color.g = game->p1_color->g;
		color.b = game->p1_color->b;
	}
	else if (type == 'o')
	{
		color.r = game->p1_color->r + (game->p1_color->r ? 127 : 0);
		color.g = game->p1_color->g + (game->p1_color->g ? 127 : 0);
		color.b = game->p1_color->b + (game->p1_color->b ? 127 : 0);
	}
	else if (type == 'X')
	{
		color.r = game->p2_color->r;
		color.g = game->p2_color->g;
		color.b = game->p2_color->b;
	}
	else if (type == 'x')
	{
		color.r = game->p2_color->r + (game->p2_color->r ? 127 : 0);
		color.g = game->p2_color->g + (game->p2_color->g ? 127 : 0);
		color.b = game->p2_color->b + (game->p2_color->b ? 127 : 0);
	}
	else
		ft_bzero(&color, sizeof(color));
	if (SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0))
		error(SDL_GetError());
}

static void			render_map(SDL_Renderer *renderer, t_filler_vis *game)
{
	SDL_Rect *rect;
	char	**board;
	char	*line;
	float x;
	float y;
	float height;
	float width;

	set_color(renderer, game, 0);
	if (SDL_RenderClear(renderer))
		error(SDL_GetError());
	height = (FILLER_SCREEN_HEIGHT - 150) / game->height;
	width = (FILLER_SCREEN_WIDTH - 50) / game->width;
	y = 25;
	board = game->board_states->board;
	while (*++board)
	{
		x = 25;
		line = *board + 3;
		while (*line++)
		{
			set_color(renderer, game, *line);
			rect = get_rectangle((int)x, (int)y, (int)(x + width), (int)height);
			if (SDL_RenderFillRect(renderer, rect))
				error(SDL_GetError());
			x += width;
			free(rect);
		}
		y += height;
	}
}

static void			print_board(char **board)
{
	while (*board)
	{
		ft_putstr(*board++);
		write(1, "\n", 1);
	}
	write(1, "\n", 1);
}

static void			key_handler(SDL_Event *e, t_filler_vis *game, t_vis_status *status)
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
}

void 				visualize(SDL_Renderer *renderer, t_filler_vis *game)
{
	SDL_Event		e;
	t_vis_status	status;
	int				speed_counter;

	status.quit = 0;
	status.pause = 0;
	status.ended = 0;
	status.speed = 0;
	status.print = 0;
	speed_counter = 0;
	while (!status.quit)
	{
		if (speed_counter)
			--speed_counter;
		if (!status.ended)
			get_next_board(game, game->height);
		render_map(renderer, game);
		put_score(renderer, game);
		SDL_RenderPresent(renderer);
		if (game->board_states->last)
		{
			status.ended = -1;
			status.pause = -1;
		}
		if (!status.pause && !speed_counter && game->board_states->right)
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
