/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_visualizer.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 21:56:50 by smorty            #+#    #+#             */
/*   Updated: 2019/08/26 23:38:08 by smorty           ###   ########.fr       */
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
#define O_COLOR_DEF 0x00C800
#define X_COLOR_DEF 0xE05A07
#define O_COLOR_1 0x09279E
#define X_COLOR_1 0xAB0F58
#define O_COLOR_2 0xE01507
#define X_COLOR_2 0x07D9E0

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
	SDL_Renderer	*renderer;
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
	int				controls;
	int				color;
}				t_vis_status;

void		error(const char *error_msg);
char		*read_input(void);
void		init_visualizer(SDL_Window **window, t_filler_vis **game);
void		get_next_board(t_filler_vis *game, int height);
void 		visualization_loop(t_filler_vis *game);
void		visualize(t_filler_vis *game, int cotrols);
void		render_board(t_filler_vis *game);
void		create_frame(t_filler_vis *game, int width, int height);
void		put_text(t_filler_vis *game, SDL_Rect *rect, char *text, int scale);

#endif
