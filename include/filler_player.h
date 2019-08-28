/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_player.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:22:01 by smorty            #+#    #+#             */
/*   Updated: 2019/08/28 23:38:32 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_PLAYER_H
# define FILLER_PLAYER_H

# include "filler_shared.h"
# include "ft_printf.h"

# define O_PLAYER -33
# define X_PLAYER -77

typedef struct	s_play
{
	int		val;
	int		x;
	int		y;
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

t_filler		*init_bot(char *player_line);
void			heat_map(t_filler *bot);
int				solve(t_filler *bot);
void			find_move(t_filler *bot, const t_piece *token);

#endif
