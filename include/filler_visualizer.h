/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_visualizer.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 21:56:50 by smorty            #+#    #+#             */
/*   Updated: 2019/08/24 14:45:34 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_VISUALZIER_H
#define FILLER_VISUALZIER_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "ft_printf.h"
#include "libft.h"

#define BUFF_SIZE 2
#define FILLER_SCREEN_HEIGHT 1200
#define FILLER_SCREEN_WIDTH 1920

typedef struct	s_board
{
	char			**board;
	int				last;
	struct s_board	*right;
	struct s_board	*left;
}				t_board;

typedef struct	s_filler_vis
{
	char			*p1_name;
	char			*p2_name;
	int				width;
	int				height;
	TTF_Font		*font;
	t_board			*board_states;
}				t_filler_vis;

typedef struct	s_vis_status
{
	int				quit;
	int				pause;
	int				speed;
	int				ended;
}				t_vis_status;

void		error(void);
char		*read_input(void);
void		init_visualizer(SDL_Window **window, SDL_Renderer **renderer, t_filler_vis **game);

#endif
