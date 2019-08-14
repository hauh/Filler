/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 16:25:21 by smorty            #+#    #+#             */
/*   Updated: 2019/08/14 21:14:43 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void    print_piece(t_piece *token)
{
	int y;

	printf("size %d %d\n", token->width, token->height);
	y = token->height;
	while (y--)
		printf("%s\n", token->fig[y]);
}

void    print_board(t_filler *bot)
{
	int x;
	int y;

	y = 0;
	while (y < bot->height)
	{
		x = 0;
		while (x < bot->width)
		{
			if (bot->board[y][x] == O_PLAYER)
				printf("\e[32m%3c\e[37m", 'O');
			else if (bot->board[y][x] == X_PLAYER)
				printf("\e[32m%3c\e[37m", 'X');
			else
				printf("%3d", bot->board[y][x]);
			++x;
		}
		printf("\n");
		++y;
	}
	printf("\n");
}
