/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visualizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 22:56:54 by smorty            #+#    #+#             */
/*   Updated: 2019/08/25 20:31:11 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler_visualizer.h"

static char			*get_name(void)
{
	char *buf;
	char *p;

	p = (buf = read_input());
	while (*p)
		++p;
	*--p = 0;
	while (*p != '/' && *p != '[')
		--p;
	if (!(p = ft_strdup(++p)))
		error(strerror(errno));
	free(buf);
	return (p);
}

static SDL_Color	*get_color(int n)
{
	SDL_Color	*color;

	if (!(color = (SDL_Color *)malloc(sizeof(SDL_Color))))
		error(strerror(errno));
	color->a = 0;
	if (n == 1)
	{
		color->r = (O_DEF_COLOR >> 16) & 0xff;
		color->g = (O_DEF_COLOR >> 8) & 0xff;
		color->b = O_DEF_COLOR & 0xff;
	}
	else
	{
		color->r = (X_DEF_COLOR >> 16) & 0xff;
		color->g = (X_DEF_COLOR >> 8) & 0xff;
		color->b = X_DEF_COLOR & 0xff;
	}
	return (color);
}

static t_filler_vis	*init_filler(void)
{
	t_filler_vis	*game;
	char			*buf;
	char			*p;

	if (!(game = (t_filler_vis *)malloc(sizeof(t_filler_vis))))
		error(strerror(errno));
	buf = read_input();
	while (*buf != 'l')
	{
		free(buf);
		buf = read_input();
	}
	free(buf);
	game->p1_name = get_name();
	game->p1_color = get_color(1);
	free((buf = read_input()));
	game->p2_name = get_name();
	game->p2_color = get_color(2);
	p = (buf = read_input());
	while (*p != ' ')
		++p;
	game->height = ft_atoi(++p);
	while (*p != ' ')
		++p;
	game->width = ft_atoi(++p);
	free(buf);
	game->board_states = NULL;
	if (!(game->font = TTF_OpenFont(
			"/srcs/OpenSans-Semibold.ttf", 72)))
		error(TTF_GetError());
	return (game);
}

void				init_visualizer(SDL_Window **window,
								SDL_Renderer **renderer, t_filler_vis **game)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		error(SDL_GetError());
	if (TTF_Init())
		error(TTF_GetError());
	if (!(*window = SDL_CreateWindow("smorty's Filler", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1920, 1200, SDL_WINDOW_SHOWN)))
		error(SDL_GetError());
	if (!(*renderer = SDL_CreateRenderer(*window, -1, 0)))
		error(SDL_GetError());
	*game = init_filler();
}
