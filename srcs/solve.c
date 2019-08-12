/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 19:53:59 by smorty            #+#    #+#             */
/*   Updated: 2019/08/12 23:16:34 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static t_piece	*get_piece(void)
{
	t_piece	*new;
	char	*line;
	char	*p;
	int		i;

	if (!(new = (t_piece *)malloc(sizeof(t_piece))))
		error();
	line = read_input();
	p = line;
	while (*p != ' ')
		++p;
	new->y = ft_atoi(++p);
	while (*p != ' ')
		++p;
	new->x = ft_atoi(++p);
	i = new->y;
	free(line);
	if (!(new->fig = (char **)malloc(sizeof(char *) * (i + 1))))
		error();
	new->fig[i] = NULL;
	while (i--)
		new->fig[i] = read_input();
	return (new);
}

void			check_piece(t_piece *token)
{
	int y;

	printf("size %d %d\n", token->x, token->y);
	y = token->y;
	while (y--)
		printf("%s\n", token->fig[y]);
}

static void		warm_up(t_filler *bot, int y, int x)
{
	int i;
	int temperature;

	temperature = 0;
	i = y - 1;
//	printf("%d %d\n", x, y);
	while (i >= 0 && bot->board[i][x] != bot->player && bot->board[i][x] != bot->opponent)
		bot->board[i--][x] = ++temperature;
	temperature = 0;
	i = y + 1;
	while (i < bot->y && bot->board[i][x] != bot->player && bot->board[i][x] != bot->opponent)
		bot->board[i++][x] = ++temperature;
	temperature = 0;
	i = x - 1;
	while (i >= 0 && bot->board[y][i] != bot->player && bot->board[y][i] != bot->opponent)
		bot->board[y][i--] = ++temperature;
	temperature = 0;
	i = x + 1;
	while (i < bot->x && bot->board[y][i] != bot->player && bot->board[y][i] != bot->opponent)
		bot->board[y][i++] = ++temperature;
}

static void		heat_map(t_filler *bot)
{
	int x;
	int y;

	y = bot->y;
	while (y--)
	{
		x = bot->x;
		while (x--)
			if (bot->board[y][x] == bot->opponent)
				warm_up(bot, y, x);
	}
}

static void	print_board(t_filler *bot)
{
	int x;
	int y;

	y = 0;
	while (y < bot->y)
	{
		x = 0;
		while (x < bot->x)
			printf("%4d", bot->board[y][x++]);
		printf("\n");
		++y;
	}
}

void	solve(t_filler *bot)
{
	t_piece *token;

	token = get_piece();
	check_piece(token);
	heat_map(bot);
	print_board(bot);
	(void)bot;
}
