/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 15:35:09 by smorty            #+#    #+#             */
/*   Updated: 2019/08/28 21:53:00 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler_player.h"

static int	warm_up(t_filler *bot, int x, int y, const int temperature)
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

static void	warmth_from_walls(t_filler *bot, const int temperature)
{
	int x;
	int y;
	int min_x;
	int min_y;

	y = bot->height;
	while (y--)
	{
		x = bot->width;
		while (x--)
			if (!bot->board[y][x])
			{
				min_x = x < bot->height / 2 ? x : bot->height - x - 1;
				min_y = y < bot->height / 2 ? y : bot->height - y - 1;
				bot->board[y][x] = temperature + min_x < min_y ? min_x : min_y;
			}
	}
}

static void	init_warmth(t_filler *bot)
{
	int x;
	int y;
	int opp_count;

	opp_count = 0;
	y = bot->height;
	while (y--)
	{
		x = bot->width;
		while (x--)
			if (bot->board[y][x] == bot->opponent)
				opp_count += warm_up(bot, x, y, 1);
	}
	if (opp_count == bot->opp_size)
		bot->opp_blocked = 1;
	else
		bot->opp_size = opp_count;
}

void		heat_map(t_filler *bot)
{
	int x;
	int y;
	int temperature;
	int warmed;

	init_warmth(bot);
	temperature = 0;
	if (!bot->opp_blocked)
	{
		warmed = 1;
		while (warmed)
		{
			warmed = 0;
			++temperature;
			y = bot->height;
			while (y--)
			{
				x = bot->width;
				while (x--)
					if (bot->board[y][x] == temperature)
						warmed = warm_up(bot, x, y, temperature + 1);
			}
		}
	}
	warmth_from_walls(bot, temperature + 5);
}
