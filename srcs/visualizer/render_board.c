/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_board.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 17:38:31 by smorty            #+#    #+#             */
/*   Updated: 2019/08/26 23:11:27 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler_visualizer.h"

static void		put_rectangle(t_filler_vis *game, SDL_Rect *rect, char type)
{
	SDL_Color color;

	if (type == 'O')
	{
		color.r = game->p1_color->r;
		color.g = game->p1_color->g;
		color.b = game->p1_color->b;
	}
	else if (type == 'X')
	{
		color.r = game->p2_color->r;
		color.g = game->p2_color->g;
		color.b = game->p2_color->b;
	}
	else if (type == 'x' || type == 'o')
		ft_memset(&color, 200, sizeof(SDL_Color));
	else
		return ;
	color.a = 0;
	if (SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 0)
		|| SDL_RenderFillRect(game->renderer, rect))
		error(SDL_GetError());
}

static void		render_line(t_filler_vis *game, SDL_Rect *rect,
							char *line, float delta_w)
{
	float round_w;

	rect->x = 25;
	round_w = 0.0;
	while (*line++)
	{
		if ((round_w += delta_w) >= 1.0)
			rect->w += 1;
		put_rectangle(game, rect, *line);
		rect->x += rect->w + 1;
		if (round_w >= 1.0)
		{
			round_w -= 1.0;
			rect->w -= 1;
		}
	}
}

static SDL_Rect	*get_rectangle(int w, int h, float *delta_w, float *delta_h)
{
	SDL_Rect *rect;

	if (!(rect = (SDL_Rect *)malloc(sizeof(SDL_Rect))))
		error(strerror(errno));
	*delta_w = (float)(FILLER_SCREEN_WIDTH - 50 - w) / (float)w;
	rect->w = (int)*delta_w;
	*delta_w -= rect->w;
	*delta_h = (float)(FILLER_SCREEN_HEIGHT - 120 - h) / (float)h;
	rect->h = (int)*delta_h;
	*delta_h -= rect->h;
	return (rect);
}

void			render_board(t_filler_vis *game)
{
	SDL_Rect	*rect;
	char		**board;
	float		delta_w;
	float		delta_h;
	float		round_h;

	rect = get_rectangle(game->width, game->height, &delta_w, &delta_h);
	rect->y = 25;
	round_h = 0.0;
	board = game->board_states->board;
	while (*++board)
	{
		if ((round_h += delta_h) >= 1.0)
			rect->h += 1;
		render_line(game, rect, *board + 3, delta_w);
		rect->y += rect->h + 1;
		if (round_h >= 1.0)
		{
			round_h -= 1.0;
			rect->h -= 1;
		}
	}
	free(rect);
}
