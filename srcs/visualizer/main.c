/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 21:42:24 by smorty            #+#    #+#             */
/*   Updated: 2019/08/25 18:00:27 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler_visualizer.h"

static void		cleanup(SDL_Window *window, SDL_Renderer *renderer, t_filler_vis *game)
{
	t_board	*p;
	char	*buf;
	int		i;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	while ((buf = read_input()))
		free(buf);
	if ((p = game->board_states))
	{
		while (p->left)
			p = p->left;
		while (p->right)
		{
			i = game->height;
			while (i--)
				free(p->board[i]);
			free(p->board);
			p = p->right;
			free(p->left);
		}
		i = game->height;
		while (i--)
			free(p->board[i]);
		free(p->board);
		free(p);
	}
	free(game->p1_name);
	free(game->p2_name);
	free(game);
}

int				main(void)
{
    SDL_Window		*window;
	SDL_Renderer	*renderer;
	t_filler_vis	*game;

	window = NULL;
	renderer = NULL;
	init_visualizer(&window, &renderer, &game);
	visualize(renderer, game);
	cleanup(window, renderer, game);
	close(0);
	close(1);
	return (0);
}
