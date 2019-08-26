/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visualizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 22:56:54 by smorty            #+#    #+#             */
/*   Updated: 2019/08/26 23:30:48 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler_visualizer.h"

static char			*get_name(void)
{
	char *buf;
	char *p;

	buf = read_input();
	p = buf;
	while (*p)
		++p;
	while (*p != '.')
		--p;
	*p = 0;
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
		color->r = (O_COLOR_DEF >> 16) & 0xff;
		color->g = (O_COLOR_DEF >> 8) & 0xff;
		color->b = O_COLOR_DEF & 0xff;
	}
	else
	{
		color->r = (X_COLOR_DEF >> 16) & 0xff;
		color->g = (X_COLOR_DEF >> 8) & 0xff;
		color->b = X_COLOR_DEF & 0xff;
	}
	return (color);
}

static void			get_game_info(t_filler_vis *game)
{
	char			*buf;
	char			*p;

	game->p1_name = get_name();
	game->p1_color = get_color(1);
	free(read_input());
	game->p2_name = get_name();
	game->p2_color = get_color(2);
	buf = read_input();
	p = buf;
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
}

static t_filler_vis	*init_filler(void)
{
	t_filler_vis	*game;
	char			*buf;

	buf = read_input();
	if (!ft_strnequ(buf, "# -------------- VM", 19))
		error("Wrong input\n");
	if (!(game = (t_filler_vis *)malloc(sizeof(t_filler_vis))))
		error(strerror(errno));
	while (*buf != 'l')
	{
		free(buf);
		buf = read_input();
	}
	free(buf);
	get_game_info(game);
	game->renderer = NULL;
	return (game);
}

void				init_visualizer(SDL_Window **window, t_filler_vis **game)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		error(SDL_GetError());
	if (!(*window = SDL_CreateWindow("smorty's Filler",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		FILLER_SCREEN_WIDTH, FILLER_SCREEN_HEIGHT, SDL_WINDOW_SHOWN)))
		error(SDL_GetError());
	if (TTF_Init())
		error(TTF_GetError());
	*game = init_filler();
	if (!((*game)->renderer = SDL_CreateRenderer(*window, -1, 0)))
		error(SDL_GetError());
}
