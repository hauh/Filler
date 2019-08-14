/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:22:01 by smorty            #+#    #+#             */
/*   Updated: 2019/08/14 19:19:43 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

#include <stdio.h> //remove
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <errno.h>
#include "libft.h"

#define BUFF_SIZE 49
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
	char	**fig;
	int		width;
	int		height;
}				t_piece;

typedef struct	s_filler
{
	int		**board;
	int		width;
	int		height;
	int		player;
	int		opponent;
	t_play	*move;
}				t_filler;

void		error(void);
char		*read_input(void);
t_filler	*init();
void		read_board(int **board, int rows);
void        heat_map(t_filler *bot);
void		solve(t_filler *bot);

void    print_board(t_filler *bot);
void    print_piece(t_piece *token);

#endif