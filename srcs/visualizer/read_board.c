/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_board.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 16:10:15 by smorty            #+#    #+#             */
/*   Updated: 2019/08/27 16:51:24 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler_visualizer.h"

static void		get_score(t_board *new, int y)
{
	int os;
	int xs;
	int i;

	os = 0;
	xs = 0;
	while (y)
	{
		i = 4;
		while (new->board[y][i])
		{
			if (new->board[y][i] == 'O' || new->board[y][i] == 'o')
				++os;
			else if (new->board[y][i] == 'X' || new->board[y][i] == 'x')
				++xs;
			++i;
		}
		--y;
	}
	new->os = os;
	new->xs = xs;
}

static char		**get_board(char *first_line, int y)
{
	char	**board;
	int		i;

	if (!(board = (char **)malloc(sizeof(char *) * (y + 2))))
		error(strerror(errno));
	i = 0;
	board[i++] = first_line;
	while (i <= y)
		board[i++] = read_input();
	board[i] = NULL;
	return (board);
}

static t_board	*new_board(t_board *prev, int y)
{
	t_board	*new;
	char	*buf;

	buf = read_input();
	while (buf && *buf != ' ')
	{
		free(buf);
		buf = read_input();
	}
	if (!buf)
	{
		if (prev)
			prev->last = 1;
		return (NULL);
	}
	if (!(new = (t_board *)malloc(sizeof(t_board))))
		error(strerror(errno));
	new->board = get_board(buf, y);
	new->right = NULL;
	new->left = prev;
	if (prev)
		prev->right = new;
	new->last = 0;
	get_score(new, y);
	return (new);
}

void			get_next_board(t_filler_vis *game, int height)
{
	t_board	*p;
	char	*buf;

	if ((buf = read_input()))
	{
		free(buf);
		if (game->board_states)
		{
			p = game->board_states;
			while (p->right)
				p = p->right;
			p->right = new_board(p, height);
		}
		else if (!(game->board_states = new_board(NULL, height)))
			error("Error on input\n");
	}
}
