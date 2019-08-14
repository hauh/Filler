/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 19:53:59 by smorty            #+#    #+#             */
/*   Updated: 2019/08/14 21:59:51 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		read_board(int **board, int rows)
{
	char	*line;
	char	*p;
	int		y;

	y = 0;
	line = read_input();
	while (*line != ' ')
	{
		free(line);
		line = read_input();
	}
	free(line);
	while (rows--)
	{
		line = read_input();
		p = line;
		while (*p)
		{
			if (*p == 'o' || *p == 'O')
				board[y][p - line - 4] = O_PLAYER;
			else if (*p == 'x' || *p == 'X')
				board[y][p - line - 4] = X_PLAYER;
			++p;
		}
		++y;
		free(line);
	}
}

static t_piece	*get_piece(void)
{
	t_piece	*new;
	char	*line;
	char	*p;
	int		i;

	if (!(new = (t_piece *)malloc(sizeof(t_piece))))
		error();
	p = (line = read_input());
	while (*p != ' ')
		++p;
	new->height = ft_atoi(++p);
	while (*p != ' ')
		++p;
	new->width = ft_atoi(++p);
	i = new->height;
	free(line);
	if (!(new->fig = (char **)malloc(sizeof(char *) * (i + 1))))
		error();
	new->fig[i] = NULL;
	while (i--)
		new->fig[i] = read_input();
	return (new);
}

static int	check_fig_position(t_filler *bot, t_piece *token, int x, int y)
{
	int t_x;
	int t_y;
	int pos_value;
	int intersections;

	if (x < 0 || y < 0)
		return (0);
	intersections = 0;
	pos_value = 0;
	t_y = token->height;
	while (t_y--)
	{
		t_x = token->width;
		while (t_x--)
		{
			if (bot->board[y + t_y][x + t_x] == bot->opponent)
				return (0);
			if (bot->board[y + t_y][x + t_x] == bot->player && token->fig[t_y][t_x] == '*' && ++intersections > 1)
				return(0);
			if (token->fig[t_y][t_x] == '*' && bot->board[y + t_y][x + t_x] != bot->player)
				pos_value += bot->board[y + t_y][x + t_x];
		}
	}
	return (intersections == 1 ? pos_value : 0);
}

static void	check_spot(t_filler *bot, t_piece *token, int x, int y)
{
	int t_x;
	int t_y;
	int pos_value;

	t_y = token->height;
	while (t_y--)
		if (y + t_y < bot->height)
		{
			t_x = token->width;
			while (t_x--)
				if (x + t_x < bot->width
					&& (pos_value = check_fig_position(bot, token, x - t_x, y - t_y))
					&& bot->move->val < pos_value)
					{
						bot->move->val = pos_value;
						bot->move->x = x - t_x;
						bot->move->y = y - t_y;
					}
		}
}

void	solve_board(t_filler *bot, t_piece *token)
{
	int x;
	int y;

	y = bot->height;
	while (y--)
	{
		x = bot->width;
		while (x--)
			if (bot->board[y][x] == bot->player)
				check_spot(bot, token, x, y);
	}
}

void	clean_last_move(t_play *move, t_piece *token)
{
	char	buf;
	int		i;

	i = token->height;
	while (i--)
		free(token->fig[i]);
	free(token->fig);
	free(token);
	move->val = -1;
	move->x = -1;
	move->y = -1;
	while (read(0, &buf, 1) > 0)
		;
}

void		solve(t_filler *bot)
{
	t_piece	*token;

	read_board(bot->board, bot->height);
	token = get_piece();
	heat_map(bot);
	solve_board(bot, token);
//	printf("1 1\n");
	if (bot->move->val > 0)
		printf("%d %d\n", bot->move->y, bot->move->x);
//	else
//	clean_last_move(bot->move, token);
}
