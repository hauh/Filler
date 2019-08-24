/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visualizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 22:56:54 by smorty            #+#    #+#             */
/*   Updated: 2019/08/24 14:47:10 by smorty           ###   ########.fr       */
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
	if (!(p = ft_strdup(p)))
		exit(-1);
	free(buf);
	return (p);
}

static t_filler_vis	*init_filler(void)
{
	t_filler_vis	*game;
	char			*buf;
	char			*p;

	if (!(game = (t_filler_vis *)malloc(sizeof(t_filler_vis))))
		exit(-1);
	buf = read_input();
	while (*buf != 'l')
	{
		free(buf);
		buf = read_input();
	}
	free(buf);
	game->p1_name = get_name();
	free((buf = read_input()));
	game->p2_name = get_name();
	p = (buf = read_input());
	while (*p != ' ')
		++p;
	game->height = ft_atoi(++p);
	while (*p != ' ')
		++p;
	game->width = ft_atoi(++p);
	free(buf);
	return (game);
}

void				init_visualizer(SDL_Window **window,
									SDL_Renderer **renderer, t_filler_vis **game)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		ft_printf("SDL_Init error: %s\n", SDL_GetError());
		exit (-1);
	}
	*window = SDL_CreateWindow("smorty's Filler", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1920, 1200, SDL_WINDOW_SHOWN);
	if (!*window)
	{
		ft_printf("SDL_CreateWindow error: %s\n", SDL_GetError());
		exit (-1);
	}
	*renderer = SDL_CreateRenderer(*window, -1, 0);
	if (!*renderer)
	{
		ft_printf("SDL_CreateRenderer error: %s\n", SDL_GetError());
		exit (-1);
	}
	*game = init_filler();
	TTF_Init();
	(*game)->font = TTF_OpenFont("/Users/smorty/42/filler/srcs/OpenSans-Semibold.ttf", 20);
	if (!(*game)->font)
		ft_printf("TTF_Init: %s\n", TTF_GetError());
}
