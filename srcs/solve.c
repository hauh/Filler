/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 19:53:59 by smorty            #+#    #+#             */
/*   Updated: 2019/08/13 23:04:13 by smorty           ###   ########.fr       */
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

static void	print_board(t_filler *bot)
{
	int x;
	int y;

	y = 0;
	while (y < bot->y)
	{
		x = 0;
		while (x < bot->x)
		{
			if (bot->board[y][x] < 0)
				printf("\e[32m%3c\e[37m", bot->board[y][x] + 100);
			else
				printf("%3d", bot->board[y][x]);
			++x;
		}
		printf("\n");
		++y;
	}
	printf("\n");
}

static void		warm_up(t_filler *bot, int x, int y, int temperature)
{
	if (x - 1 >= 0 && !bot->board[y][x - 1])
		bot->board[y][x - 1] = temperature;
	if (x + 1 < bot->x && !bot->board[y][x + 1])
		bot->board[y][x + 1] = temperature;
	if (x - 1 >= 0 && y - 1 >= 0 && !bot->board[y - 1][x - 1])
		bot->board[y - 1][x - 1] = temperature;
	if (x + 1 < bot->x && y - 1 >= 0 && !bot->board[y - 1][x + 1])
		bot->board[y - 1][x + 1] = temperature;
	if (y - 1 >= 0 && !bot->board[y - 1][x])
		bot->board[y - 1][x] = temperature;
	if (y + 1 < bot->y && !bot->board[y + 1][x])
		bot->board[y + 1][x] = temperature;
	if (x + 1 < bot->x && y + 1 < bot->y && !bot->board[y + 1][x + 1])
		bot->board[y + 1][x + 1] = temperature;
	if (x - 1 >= 0 && y + 1 < bot->y && !bot->board[y + 1][x - 1])
		bot->board[y + 1][x - 1] = temperature;
}

static int		is_cold(t_filler *bot)
{
	int x;
	int y;

	y = bot->y;
	while (y--)
	{
		x = bot->x;
		while (x--)
			if (!bot->board[y][x])
				return (1);
	}
	return (0);
}

static void		heat_map(t_filler *bot)
{
	int x;
	int y;
	int temperature;

	temperature = 1;
	y = bot->y;
	while (y--)
	{
		x = bot->x;
		while (x--)
			if (bot->board[y][x] == bot->opponent)
				warm_up(bot, x, y, temperature);
	}
	while (is_cold(bot))
	{
		y = bot->y;
		while (y--)
		{
			x = bot->x;
			while (x--)
				if (bot->board[y][x] == temperature)
					warm_up(bot, x, y, temperature + 1);
		}
		++temperature;
	}
}

static int	check_fig_position(t_filler *bot, t_piece *token, int shift_x, int shift_y, int x, int y)
{

}

static void	check_spot(t_filler *bot, t_piece *token, int x, int y)
{
	int t_x;
	int t_y;
	int pos_value;
	int intersections;

	intersections = 0;
	t_y = token->y;
	while (t_y--)
		if (y + t_y < bot->y)
		{
			t_x = token->x;
			while (t_x--)
				if (x + t_x < bot->x
					&& (pos_value = check_fig_position(bot, token, t_x, t_y, x, y))
					&& bot->move->val < pos_value)
					{
						bot->move->val = pos_value;
						bot->move->x = x + t_x;
						bot->move->y = y + t_y;
					}
		}
}

void	solve_board(t_filler *bot, t_piece *token)
{
	int x;
	int y;

	y = bot->y;
	while (y--)
	{
		x = bot->x;
		while (x--)
			if (bot->board[y][x] == bot->player)
				check_spot(bot, token, x, y);
	}
}

void	solve(t_filler *bot)
{
	t_piece *token;

	token = get_piece();
	check_piece(token);
	if (!(bot->move = (t_play *)malloc(sizeof(t_play))))
		error();
	bot->move->val = -1;
	bot->move->x = -1;
	bot->move->y = -1;
	heat_map(bot);
	print_board(bot);
}
