/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:21:23 by smorty            #+#    #+#             */
/*   Updated: 2019/08/12 21:23:05 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	error(void)
{
	ft_putstr(strerror(errno));
	exit (-1);
}

void	check_output(t_filler *bot)
{
	int x;
	int y;

	printf("player %d\n", bot->player);	
	printf("size %d %d \n", bot->x, bot->y);
	y = 0;
	while (y < bot->y)
	{
		x = 0;
		while (x < bot->x)
		{
			printf("%d ", (bot->board[y][x] ? bot->board[y][x] : 0));
			++x;
		}
		printf("\n");
		++y;
	}
}

int		main(int argc, char **argv)
{
	t_filler *bot;

	(void)argc;
	bot = init(*argv);
	check_output(bot);
	solve(bot);
	return (0);
}
