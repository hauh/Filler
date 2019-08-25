/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_visualizer.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 21:56:50 by smorty            #+#    #+#             */
/*   Updated: 2019/08/25 22:07:55 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_VISUALZIER_H
#define FILLER_VISUALZIER_H

#include <errno.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "ft_printf.h"
#include "libft.h"

#define BUFF_SIZE 2
#define FILLER_SCREEN_HEIGHT 1200
#define FILLER_SCREEN_WIDTH 1920
#define O_DEF_COLOR 0x00C800
#define X_DEF_COLOR 0xFF7F50

typedef struct	s_board
{
	char			**board;
	int				last;
	int				xs;
	int				os;
	struct s_board	*right;
	struct s_board	*left;
}				t_board;

typedef struct	s_filler_vis
{
	char			*p1_name;
	char			*p2_name;
	SDL_Color		*p1_color;
	SDL_Color		*p2_color;
	TTF_Font		*font;
	int				width;
	int				height;
	t_board			*board_states;
}				t_filler_vis;

typedef struct	s_vis_status
{
	int				quit;
	int				pause;
	int				speed;
	int				ended;
	int				print;
}				t_vis_status;

void		error(const char *error_msg);
char		*read_input(void);
void		init_visualizer(SDL_Window **window, SDL_Renderer **renderer, t_filler_vis **game);
void		get_next_board(t_filler_vis *game, int height);
void 		visualize(SDL_Renderer *renderer, t_filler_vis *game);
void		put_score(SDL_Renderer *renderer, t_filler_vis *game);
SDL_Rect	*get_rectangle(int x, int y, int width, int height);

#endif
