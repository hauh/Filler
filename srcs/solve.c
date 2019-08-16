/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 19:53:59 by smorty            #+#    #+#             */
/*   Updated: 2019/08/16 23:29:55 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		read_board(int **board, int rows)
{
	char	*line;
	char	*p;
	int		y;

	y = 0;
	free((line = read_input()));
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

t_piece	*get_piece(void)
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
	free(line);
	if (!(new->fig = (char **)malloc(sizeof(char *) * (new->height + 1))))
		error();
	i = 0;
	while (i < new->height)
		new->fig[i++] = read_input();
	new->fig[i] = NULL;
	return (new);
}

static int	check_fig_position(t_filler *bot, t_piece *token, int x, int y)
{
	int t_x;
	int t_y;
	int pos_value;
	int intersections;

	if (x < 0 || y < 0 || x + token->width > bot->width || y + token->height > bot->height)
		return (0xffff);
	intersections = 0;
	pos_value = 0;
	t_y = 0;
	while (t_y < token->height)
	{
		t_x = 0;
		while (t_x < token->width)
		{
			if (token->fig[t_y][t_x] == '*')
			{
				if (bot->board[y + t_y][x + t_x] == bot->opponent)
					return (0xffff);
				if (bot->board[y + t_y][x + t_x] == bot->player && ++intersections > 1)
					return (0xffff);
				if (bot->board[y + t_y][x + t_x] != bot->player)
					pos_value += bot->board[y + t_y][x + t_x];
			}
			++t_x;
		}
		++t_y;
	}
	return (intersections == 1 ? pos_value : 0xffff);
}

static void	check_spot(t_filler *bot, t_piece *token, int x, int y)
{
	int t_x;
	int t_y;
	int pos_value;

	t_y = 0;
	while (t_y < token->height)
	{
		t_x = 0;
		while (t_x < token->width)
		{
			pos_value = check_fig_position(bot, token, x - t_x, y - t_y);
			if (bot->move->val > pos_value)
			{
				bot->move->val = pos_value;
				bot->move->x = x - t_x;
				bot->move->y = y - t_y;
			}
			++t_x;
		}
		++t_y;
	}
}

void	solve_board(t_filler *bot, t_piece *token)
{
	int x;
	int y;

	y = 0;
	while (y < bot->height)
	{
		x = 0;
		while (x < bot->width)
		{
			if (bot->board[y][x] == bot->player)
				check_spot(bot, token, x, y);
			++x;
		}
		++y;
	}
}

void	clean_last_move(t_filler *bot, t_piece *token)
{
	int		i;

	i = token->height;
	while (i--)
		free(token->fig[i]);
	free(token->fig);
	free(token);
	bot->move->val = 0xffff;
	bot->move->x = 0;
	bot->move->y = 0;
	i = bot->height;
	while (i--)
		ft_bzero(bot->board[i], sizeof(int) * bot->width);
}

void		solve(t_filler *bot)
{
	t_piece	*token;

	read_board(bot->board, bot->height);
	token = get_piece();
	heat_map(bot);
	solve_board(bot, token);
	if (bot->move->val != 0xffff)
		ft_printf("%d %d\n", bot->move->y, bot->move->x);
	else
	{
		ft_printf("0 0\n", 1);
		exit(0);
	}
	clean_last_move(bot, token);
}
