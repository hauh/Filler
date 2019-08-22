/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 21:42:24 by smorty            #+#    #+#             */
/*   Updated: 2019/08/22 23:17:07 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler_visualizer.h"

static SDL_Rect	*get_rectangle(int x, int y, int width, int height)
{
	SDL_Rect *rect;

	rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
	rect->x = x;
	rect->y = y;
	rect->w = width;
	rect->h = height;
	return (rect);
}

void			render_map(SDL_Renderer *renderer, t_filler_vis *game)
{
	SDL_Rect *rect;
	int i;
	int j;
	int height;
	int width;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	height = 1200 / (game->height + 2);
	width = 1920 / (game->width + 2);
	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			if (game->board[i][j] == game->player)
				SDL_SetRenderDrawColor(renderer, 0, 200, 0, SDL_ALPHA_OPAQUE);
			else if (game->board[i][j] == game->opponent)
				SDL_SetRenderDrawColor(renderer, 0, 0, 200, SDL_ALPHA_OPAQUE);
			else
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			++j;
			rect = get_rectangle(j * width, (i + 1) * height, width, height);
			SDL_RenderFillRect(renderer, rect);
			free(rect);
		}
		++i;
	}
}

static t_board	*new_board(t_board *prev, int y)
{
	t_board	*new;
	char	*buf;
	int		i;

	if (!(new = (t_board *)malloc(sizeof(t_board))))
		exit(-1);
	buf = read_input();
	while (*buf != ' ')
	{
		free(buf);
		buf = read_input();
	}
	free(buf);
	new->board = (char **)malloc(sizeof(char) * y);
	i = 0;
	while (i < y)
		new->board[i++] = read_input();
	new->right = NULL;
	new->left = prev;
	if (prev)
		prev->right = new;
	return (new);
}

int				main(void)
{
    SDL_Window		*window;
	SDL_Renderer	*renderer;
	t_filler_vis	*game;

	window = NULL;
	renderer = NULL;
	init_visualizer(&window, &renderer, &game);
	game->board_states = new_board(NULL, game->height);
	visualize(renderer, game);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
