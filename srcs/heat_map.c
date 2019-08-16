/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 15:35:09 by smorty            #+#    #+#             */
/*   Updated: 2019/08/16 22:47:30 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	warm_up(t_filler *bot, int x, int y, int temperature)
{
	if (x - 1 >= 0 && !bot->board[y][x - 1])
		bot->board[y][x - 1] = temperature;
	if (x + 1 < bot->width && !bot->board[y][x + 1])
		bot->board[y][x + 1] = temperature;
	if (x - 1 >= 0 && y - 1 >= 0 && !bot->board[y - 1][x - 1])
		bot->board[y - 1][x - 1] = temperature;
	if (x + 1 < bot->width && y - 1 >= 0 && !bot->board[y - 1][x + 1])
		bot->board[y - 1][x + 1] = temperature;
	if (y - 1 >= 0 && !bot->board[y - 1][x])
		bot->board[y - 1][x] = temperature;
	if (y + 1 < bot->height && !bot->board[y + 1][x])
		bot->board[y + 1][x] = temperature;
	if (x + 1 < bot->width && y + 1 < bot->height && !bot->board[y + 1][x + 1])
		bot->board[y + 1][x + 1] = temperature;
	if (x - 1 >= 0 && y + 1 < bot->height && !bot->board[y + 1][x - 1])
		bot->board[y + 1][x - 1] = temperature;
	return (1);
}

static int  is_cold(t_filler *bot)
{
	int x;
	int y;

	y = bot->height;
	while (y--)
	{
		x = bot->width;
		while (x--)
			if (!bot->board[y][x])
				return (1);
	}
	return (0);
}

void        heat_map(t_filler *bot)
{
	int x;
	int y;
	int temperature;
	int check;

	temperature = 1;
	y = bot->height;
	while (y--)
	{
		x = bot->width;
		while (x--)
			if (bot->board[y][x] == bot->opponent)
				warm_up(bot, x, y, temperature);
	}
	check = 1;
	while (is_cold(bot) && check)
	{
		check = 0;
		y = bot->height;
		while (y--)
		{
			x = bot->width;
			while (x--)
				if (bot->board[y][x] == temperature)
					check = warm_up(bot, x, y, temperature + 1);
		}
		++temperature;
	}
}
