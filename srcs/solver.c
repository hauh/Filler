/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 19:53:59 by smorty            #+#    #+#             */
/*   Updated: 2019/08/22 21:52:39 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		read_board(int **board, int rows)
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

static int		*get_coords(t_piece *new)
{
	char	*line;
	char	*s;
	int		*coords;
	int		i;

	if (!(coords = (int *)malloc(sizeof(int) * new->height * new->width)))
		error();
	i = 0;
	new->size = 0;
	while (i < new->height)
	{
		s = (line = read_input());
		while (*s)
		{
			if (*s == '*')
				coords[new->size++] = (i << 16) | (s - line);
			++s;
		}
		free(line);
		++i;
	}
	return (coords);
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
	free(line);
	new->coords = get_coords(new);
	i = -1;
	return (new);
}

static void		clean_last_move(t_filler *bot, t_piece *token)
{
	int i;

	free(token->coords);
	free(token);
	bot->move->val = 0xffff;
	bot->move->x = 0;
	bot->move->y = 0;
	i = bot->height;
	while (i--)
		ft_bzero(bot->board[i], sizeof(int) * bot->width);
}

void			solve(t_filler *bot)
{
	t_piece	*token;

	read_board(bot->board, bot->height);
	token = get_piece();
	if (!bot->opp_blocked)
		heat_map(bot);
	find_move(bot, token);
	if (bot->move->val != 0xffff)
		ft_printf("%d %d\n", bot->move->y, bot->move->x);
	else
	{
		ft_printf("0 0\n", 1);
		exit(0);
	}
	clean_last_move(bot, token);
}
