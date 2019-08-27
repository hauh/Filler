/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 15:22:00 by smorty            #+#    #+#             */
/*   Updated: 2019/08/27 21:46:21 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	check_spot(t_filler *bot, t_piece *token, int x, int y)
{
	int t_x;
	int t_y;
	int size;
	int overlaps;
	int pos_value;

	size = token->size;
	overlaps = 0;
	pos_value = 0;
	while (size--)
	{
		t_y = y + (token->coords[size] >> 16);
		t_x = x + ((token->coords[size] << 16) >> 16);
		if (bot->board[t_y][t_x] == bot->opponent)
			return (0xffff);
		if (bot->board[t_y][t_x] != bot->player)
			pos_value += bot->board[t_y][t_x];
		else if (++overlaps > 1)
			return (0xffff);
	}
	return (overlaps ? pos_value : 0xffff);
}

void		find_move(t_filler *bot, t_piece *token)
{
	int x;
	int y;
	int pos_value;

	y = bot->height - token->height + 1;
	while (y--)
	{
		x = bot->width - token->width + 1;
		while (x--)
			if ((pos_value = check_spot(bot, token, x, y)) < bot->move->val)
			{
				bot->move->val = pos_value;
				bot->move->x = x;
				bot->move->y = y;
			}
	}
}
