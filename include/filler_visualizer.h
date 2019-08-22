/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_visualizer.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 21:56:50 by smorty            #+#    #+#             */
/*   Updated: 2019/08/22 23:14:08 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_VISUALZIER_H
#define FILLER_VISUALZIER_H

#include "../srcs/sdl2/include/SDL2/SDL.h"
#include "ft_printf.h"

#define BUFF_SIZE 2

typedef struct	s_board
{
	char			**board;
	struct s_board	*right;
	struct s_board	*left
}				t_board;

typedef struct	s_filler_vis
{
	char			*p1_name;
	char			*p2_name;
	int				width;
	int				height;
	t_board			*board_states;
}				t_filler_vis;

char		*read_input(void);
void		init_visualizer(SDL_Window **window, SDL_Renderer **renderer, t_filler_vis **game);

#endif
