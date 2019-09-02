/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_visual.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 21:42:24 by smorty            #+#    #+#             */
/*   Updated: 2019/09/02 17:35:36 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler_visualizer.h"

static void		clean_boards(t_board *game_state)
{
	char **clean;

	while (game_state->left)
		game_state = game_state->left;
	while (game_state->right)
	{
		clean = game_state->board;
		while (*clean)
			free(*clean++);
		free(game_state->board);
		game_state = game_state->right;
		free(game_state->left);
	}
	clean = game_state->board;
	while (*clean)
		free(*clean++);
	free(game_state->board);
	free(game_state);
}

static void		cleanup(t_filler_vis *game)
{
	char *buf;

	if ((buf = read_input()))
	{
		free(buf);
		ft_putendl("Please wait for filler_vm to finish.");
		while ((buf = read_input()))
			free(buf);
	}
	if (game->board_states)
		clean_boards(game->board_states);
	TTF_CloseFont(game->font);
	free(game->p1_color);
	free(game->p2_color);
	free(game->p1_name);
	free(game->p2_name);
	SDL_DestroyRenderer(game->renderer);
	free(game);
}

int				main(void)
{
	SDL_Window		*window;
	t_filler_vis	*game;

	window = NULL;
	init_visualizer(&window, &game);
	visualization_loop(game);
	SDL_DestroyWindow(window);
	SDL_Quit();
	cleanup(game);
	return (0);
}
