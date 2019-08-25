/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:22:01 by smorty            #+#    #+#             */
/*   Updated: 2019/08/25 16:39:46 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <errno.h>
#include "libft.h"
#include "ft_printf.h"

#define BUFF_SIZE 2
#define	O_PLAYER -33
#define	X_PLAYER -77

typedef struct	s_play
{
	int val;
	int x;
	int y;
}				t_play;

typedef struct	s_piece
{
	int		*coords;
	int		width;
	int		height;
	int		size;
}				t_piece;

typedef struct	s_filler
{
	int		**board;
	int		width;
	int		height;
	int		player;
	int		opponent;
	int		opp_size;
	int		opp_blocked;
	t_play	*move;
}				t_filler;

void		error(const char *error_msg);
char		*read_input(void);
t_filler	*init_bot(char *player_line);
void        heat_map(t_filler *bot);
void		solve(t_filler *bot);
void		find_move(t_filler *bot, t_piece *token);

#endif
