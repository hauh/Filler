/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:22:01 by smorty            #+#    #+#             */
/*   Updated: 2019/08/13 22:56:48 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

#include <stdio.h> //remove
#include <unistd.h>
#include <strings.h>
#include <errno.h>
#include "libft.h"

#define BUFF_SIZE 49
#define	O_PLAYER -21
#define	X_PLAYER -12

typedef struct	s_play
{
	int val;
	int x;
	int y;
}				t_play;


typedef struct	s_piece
{
	char	**fig;
	int		x;
	int		y;
}				t_piece;

typedef struct	s_filler
{
	int		**board;
	int		x;
	int		y;
	int		player;
	int		opponent;
	t_play	*move;
}				t_filler;

void		error(void);
char		*read_input(void);
t_filler	*init(char *name);
void		solve(t_filler *bot);

#endif