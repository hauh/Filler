/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 19:02:48 by smorty            #+#    #+#             */
/*   Updated: 2019/08/14 20:14:32 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	init_player(t_filler *bot)
{
	char	*line;
	char	*p;

	p = (line = read_input());
	while (*p != 'p')
		++p;
	if (*++p == '1')
	{
		bot->player = O_PLAYER;
		bot->opponent = X_PLAYER;
	}
	else
	{
		bot->player = X_PLAYER;
		bot->opponent = O_PLAYER;
	}
	free(line);
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

	p = (line = read_input());
	while (*p != ' ')
		++p;
	bot->height = ft_atoi(++p);
	while (*p != ' ')
		++p;
	bot->width = ft_atoi(++p);
	free(line);
	bot->board = allocate_board(bot->width, bot->height);
}

t_filler	*init(void)
{
	t_filler *bot;

	if (!(bot = (t_filler *)malloc(sizeof(t_filler))))
		error();
	init_player(bot);
	init_board(bot);
	if (!(bot->move = (t_play *)malloc(sizeof(t_play))))
		error();
	bot->move->val = -1;
	bot->move->x = -1;
	bot->move->y = -1;
	return (bot);
}
