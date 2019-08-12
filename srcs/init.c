/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 19:02:48 by smorty            #+#    #+#             */
/*   Updated: 2019/08/12 22:55:47 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	init_player(char *name)
{
	char	*line;
	char	*p;
	int		player;

	line = read_input();
	while (*line != '$')
	{
		free(line);
		line = read_input();
	}
	p = line;
	while (*p != ']')
		++p;
	*p = 0;
	p -= ft_strlen(name);
	player = ft_strequ(p, name) ? O_PLAYER : X_PLAYER;
	free(line);
	return (player);
}

static int	**allocate_board(int x, int y)
{
	int **board;

	if (!(board = (int **)malloc(sizeof(int *) * y)))
		error();
	while (y--)
	{
		if (!(board[y] = (int *)malloc(sizeof(int) * x)))
			error();
		ft_bzero(board[y], sizeof(int) * x);
	}
	return (board);
}

static void	init_board(t_filler *bot)
{
	char *line;
	char *p;

	line = read_input();
	while (*line != 'P')
	{
		free(line);
		line = read_input();
	}
	p = line;
	while (*p != ' ')
		++p;
	bot->y = ft_atoi(++p);
	while (*p != ' ')
		++p;
	bot->x = ft_atoi(++p);
	free(line);
	bot->board = allocate_board(bot->x, bot->y);
}

static void	read_board(int **board, int rows)
{
	char	*line;
	char	*p;
	int		x;
	int		y;

	y = 0;
	line = read_input();
	while (rows--)
	{
		free(line);
		line = read_input();
		p = line;
		x = -4;
		while (*p)
		{
			if (*p == 'o' || *p == 'O' || *p == 'x' || *p == 'X')
				board[y][x] = (int)*p - 100;
			++x;
			++p;
		}
		++y;
	}
	free(line);
}

t_filler	*init(char *name)
{
	t_filler *bot;

	if (!(bot = (t_filler *)malloc(sizeof(t_filler))))
		error();
	bot->player = init_player(name);
	bot->opponent = (bot->player == X_PLAYER ? O_PLAYER : X_PLAYER);
	init_board(bot);
	read_board(bot->board, bot->y);
	return (bot);
}
