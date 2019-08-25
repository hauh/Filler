/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_score.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 18:15:13 by smorty            #+#    #+#             */
/*   Updated: 2019/08/25 20:57:21 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler_visualizer.h"

static SDL_Color	*get_color(t_filler_vis *game, char *text)
{
	SDL_Color *color;

	if (!(color = (SDL_Color *)malloc(sizeof(SDL_Color))))
		error(strerror(errno));
	color->a = 0;
	if (ft_strequ(text, "P1 "))
	{
		color->r = game->p1_color->r;
		color->g = game->p1_color->g;
		color->b = game->p1_color->b;
	}
	else if (ft_strequ(text, "P2 "))
	{
		color->r = game->p2_color->r;
		color->g = game->p2_color->g;
		color->b = game->p2_color->b;
	}
	else
	{
		color->r = 200;
		color->g = 200;
		color->b = 200;
	}
	return (color);
}

static int			put_text(SDL_Renderer *renderer, t_filler_vis *game, char *text, int x)
{
	SDL_Surface	*surface;
	SDL_Texture	*texture;
	SDL_Color	*color;
	SDL_Rect	*rect;
	int			width;

	color = get_color(game, text);
	if (!(surface = TTF_RenderText_Blended(game->font, text, *color)))
		error(SDL_GetError());
	if (!(texture = SDL_CreateTextureFromSurface(renderer, surface)))
		error(SDL_GetError());
	width = ft_strlen(text) * 25;
	rect = get_rectangle(x, FILLER_SCREEN_HEIGHT / 12 * 11, width, 100);
	if (SDL_RenderCopy(renderer, texture, NULL, rect))
		error(SDL_GetError());
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	free(color);
	free(rect);
	return (width);
}

void				put_score(SDL_Renderer *renderer, t_filler_vis *game)
{
	char	*text;
	int		x;

	x = FILLER_SCREEN_WIDTH / 100;
	x += put_text(renderer, game, "P1 ", x);
	x += put_text(renderer, game, game->p1_name, x);
	x += put_text(renderer, game, ": ", x);
	text = ft_itoa(game->board_states->os);
	x += put_text(renderer, game, text, x);
	free(text);
	x = FILLER_SCREEN_WIDTH / 3;
	x += put_text(renderer, game, "P2 ", x);
	x += put_text(renderer, game, game->p2_name, x);
	x += put_text(renderer, game, ": ", x);
	text = ft_itoa(game->board_states->xs);
	x += put_text(renderer, game, text, x);
	free(text);
}
