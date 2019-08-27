/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 19:02:48 by smorty            #+#    #+#             */
/*   Updated: 2019/08/27 17:53:35 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	init_player(t_filler *bot, char *player_line)
{
	while (*player_line != 'p')
		++player_line;
	if (*++player_line == '1')
	{
		bot->player = O_PLAYER;
		bot->opponent = X_PLAYER;
	}
	else
	{
		bot->player = X_PLAYER;
		bot->opponent = O_PLAYER;
	}
}

static int	**allocate_board(int x, int y)
{
	int **board;

	if (!(board = (int **)malloc(sizeof(int *) * y)))
		error(strerror(errno));
	while (y--)
	{
		if (!(board[y] = (int *)malloc(sizeof(int) * x)))
			error(strerror(errno));
		ft_bzero(board[y], sizeof(int) * x);
	}
	return (board);
}

static void	init_board(t_filler *bot)
{
	char *line;
	char *p;

	line = read_input();
	p = line;
	while (*p != ' ')
		++p;
	bot->height = ft_atoi(++p);
	while (*p != ' ')
		++p;
	bot->width = ft_atoi(++p);
	free(line);
	bot->board = allocate_board(bot->width, bot->height);
}

t_filler	*init_bot(char *player_line)
{
	t_filler *bot;

	if (!(bot = (t_filler *)malloc(sizeof(t_filler))))
		error(strerror(errno));
	init_player(bot, player_line);
	init_board(bot);
	if (!(bot->move = (t_play *)malloc(sizeof(t_play))))
		error(strerror(errno));
	bot->move->val = 0xffff;
	bot->move->x = 0;
	bot->move->y = 0;
	bot->opp_size = 0;
	bot->opp_blocked = 0;
	return (bot);
}
