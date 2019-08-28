/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_visualizer.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 21:56:50 by smorty            #+#    #+#             */
/*   Updated: 2019/08/28 23:40:42 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_VISUALIZER_H
# define FILLER_VISUALIZER_H

# include "filler_shared.h"
# include "SDL.h"
# include "SDL_ttf.h"

# define FILLER_SCREEN_HEIGHT 1200
# define FILLER_SCREEN_WIDTH 1920
# define O_COLOR_DEF 0x00C800
# define X_COLOR_DEF 0xE05A07
# define O_COLOR_1 0x09279E
# define X_COLOR_1 0xAB0F58
# define O_COLOR_2 0xE01507
# define X_COLOR_2 0x07D9E0
# define O_COLOR_3 0x387923
# define X_COLOR_3 0x9A0FDB
# define O_COLOR_4 0xB047E5
# define X_COLOR_4 0x07D9E0
# define O_COLOR_5 0x802810
# define X_COLOR_5 0xEAC965
# define O_COLOR_6 0xB0fE44
# define X_COLOR_6 0xF5623E
# define O_COLOR_7 0xFF52A0
# define X_COLOR_7 0x444A0C

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

void			init_visualizer(SDL_Window **window, t_filler_vis **game);
void			get_next_board(t_filler_vis *game, int height);
void			visualization_loop(t_filler_vis *game);
void			visualize(t_filler_vis *game, int cotrols);
void			render_board(t_filler_vis *game);
void			create_frame(t_filler_vis *game, int width, int height);
void			put_text(t_filler_vis *game, SDL_Rect *rect,
							const char *text, int scale);

#endif
