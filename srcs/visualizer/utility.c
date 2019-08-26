/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 23:17:25 by smorty            #+#    #+#             */
/*   Updated: 2019/08/26 23:17:51 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler_visualizer.h"

static void	set_color(t_filler_vis *game, SDL_Color *color, char *text)
{
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
		ft_memset(color, 200, sizeof(SDL_Color));
	color->a = 0;
}

void		put_text(t_filler_vis *game, SDL_Rect *rect, char *text, int scale)
{
	SDL_Surface	*surface;
	SDL_Texture	*texture;
	SDL_Color	color;

	set_color(game, &color, text);
	if (!(surface = TTF_RenderText_Blended(game->font, text, color)))
		error(SDL_GetError());
	if (!(texture = SDL_CreateTextureFromSurface(game->renderer, surface)))
		error(SDL_GetError());
	rect->w = ft_strlen(text) * (scale > 0 ? scale : -scale);
	if (SDL_RenderCopy(game->renderer, texture, NULL, rect))
		error(SDL_GetError());
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	if (scale > 0)
		rect->x += rect->w;
	else
		rect->y += rect->h;
}

void		create_frame(t_filler_vis *game, int width, int height)
{
	SDL_Rect	rect;
	SDL_Color	color;

	rect.w = width;
	rect.h = height;
	rect.x = (FILLER_SCREEN_WIDTH - rect.w) / 2;
	rect.y = (FILLER_SCREEN_HEIGHT - rect.h) / 2;
	ft_memset(&color, 0, sizeof(SDL_Color));
	if (SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 0)
		|| SDL_RenderFillRect(game->renderer, &rect))
		error(SDL_GetError());
	color.r = game->p1_color->r + game->p2_color->r;
	color.g = game->p1_color->g + game->p2_color->g;
	color.b = game->p1_color->b + game->p2_color->b;
	if (SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 0)
		|| SDL_RenderDrawRect(game->renderer, &rect))
		error(SDL_GetError());
}
