/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 18:15:13 by smorty            #+#    #+#             */
/*   Updated: 2019/08/26 23:39:59 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler_visualizer.h"

static void	put_victory(t_filler_vis *game)
{
	SDL_Rect	rect;
	char		*victor;

	if (game->board_states->os > game->board_states->xs)
		victor = game->p1_name;
	else if (game->board_states->xs > game->board_states->os)
		victor = game->p2_name;
	else
		victor = "Draw";
	rect.w = (ft_strlen(victor) + 8) * 30 + 50;
	rect.h = 150;
	create_frame(game, rect.w, rect.h);
	rect.x = (FILLER_SCREEN_WIDTH - rect.w) / 2 + 25;
	rect.y = (FILLER_SCREEN_HEIGHT - rect.h) / 2 + 25;
	rect.h -= 50;
	if (game->board_states->os > game->board_states->xs)
		put_text(game, &rect, "P1 ", 30);
	else if (game->board_states->xs > game->board_states->os)
		put_text(game, &rect, "P2 ", 30);
	put_text(game, &rect, victor, 30);
	if (game->board_states->os != game->board_states->xs)
		put_text(game, &rect, " won!", 30);
}

static void	put_score(t_filler_vis *game)
{
	SDL_Rect	rect;
	char		*text;

	rect.x = 25;
	rect.y = FILLER_SCREEN_HEIGHT - 100;
	rect.h = 100;
	put_text(game, &rect, "P1 ", 30);
	put_text(game, &rect, game->p1_name, 30);
	put_text(game, &rect, ": ", 30);
	text = ft_itoa(game->board_states->os);
	put_text(game, &rect, text, 30);
	free(text);
	rect.x = FILLER_SCREEN_WIDTH / 3;
	put_text(game, &rect, "P2 ", 30);
	put_text(game, &rect, game->p2_name, 30);
	put_text(game, &rect, ": ", 30);
	text = ft_itoa(game->board_states->xs);
	put_text(game, &rect, text, 30);
	free(text);
}

static void	put_controls(t_filler_vis *game, int controls)
{
	SDL_Rect rect;

	rect.x = FILLER_SCREEN_WIDTH - 285;
	rect.y = FILLER_SCREEN_HEIGHT - 60;
	rect.h = 50;
	put_text(game, &rect, "Tab: controls", 20);
	if (!controls)
		return ;
	create_frame(game, 550, 370);
	rect.x = (FILLER_SCREEN_WIDTH - 550) / 2 + 25;
	rect.y = (FILLER_SCREEN_HEIGHT - 370) / 2 + 10;
	put_text(game, &rect, "Space: pause", -20);
	put_text(game, &rect, "Arrow [<-]: previous move", -20);
	put_text(game, &rect, "Arrow [->]: next move", -20);
	put_text(game, &rect, "Num [-]: slow down", -20);
	put_text(game, &rect, "Num [+]: speed up", -20);
	put_text(game, &rect, "Backspace: change colors", -20);
	put_text(game, &rect, "Escape: quit", -20);
}

void		visualize(t_filler_vis *game, int controls)
{
	if (SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 0)
		|| SDL_RenderClear(game->renderer))
		error(SDL_GetError());
	render_board(game);
	put_score(game);
	if (game->board_states->last)
		put_victory(game);
	put_controls(game, controls);
	SDL_RenderPresent(game->renderer);
}
