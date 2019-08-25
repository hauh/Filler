# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smorty <smorty@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/12 16:55:12 by smorty            #+#    #+#              #
#    Updated: 2019/08/25 18:58:26 by smorty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := smorty.filler

VISUAL := filler_visual

SRCSFILES := $(addprefix filler/, main.c init_bot.c heat_map.c solver.c find_move.c) read_input.c shared.c

SRCSFILES_VIS := $(addprefix visualizer/, main.c init_visualizer.c read_board.c visualization.c put_score.c) read_input.c shared.c

SRCDIR := srcs/

LIBSDIR := libs/

OBJDIR := $(SRCDIR)obj/

LFTDIR := $(SRCDIR)$(LIBSDIR)libft/

LFT := $(LFTDIR)libft.a

LFTPRINTFDIR := $(SRCDIR)$(LIBSDIR)ft_printf/

LFTPRINTF := $(LFTPRINTFDIR)libftprintf.a

SDL2DIR := $(SRCDIR)$(LIBSDIR)sdl2/

SDL2TTFDIR := $(SRCDIR)$(LIBSDIR)sdl2_ttf/

SDL2 := $(SDL2DIR)lib/libSDL2-2.0.0.dylib

SDL2TTF := $(SDL2TTFDIR)lib/libSDL2_ttf-2.0.0.dylib

INCLUDE := -I./include -I./$(SDL2DIR)/include/SDL2 -I./$(SDL2TTFDIR)/include/SDL2 -I./$(LFTDIR) -I./$(LFTPRINTFDIR)includes/

SRCS := $(addprefix $(SRCDIR), $(SRCSFILES))

SRCS_VIS := $(addprefix $(SRCDIR), $(SRCSFILES_VIS))

OBJ := $(SRCS:%.c=$(OBJDIR)%.o)

OBJ_VIS := $(SRCS_VIS:%.c=$(OBJDIR)%.o)

CC := gcc -Wall -Werror -Wextra

all: $(NAME) $(VISUAL)

$(NAME): $(LFT) $(LFTPRINTF) $(OBJ)
	@$(CC) $^ -o $@
	@printf "\r\e[J\e[32m$@\e[0m done!\n\e[?25h"

$(VISUAL): $(LFT) $(LFTPRINTF) $(OBJ_VIS)
	@$(CC) $^ $(SDL2) $(SDL2TTF) -o $@
	@printf "\r\e[J\e[32m$@\e[0m done!\n\e[?25h"

$(LFT):
	@$(MAKE) -C $(LFTDIR)
	@$(MAKE) -C $(LFTDIR) clean

$(LFTPRINTF):
	@$(MAKE) -C $(LFTPRINTFDIR)
	@$(MAKE) -C $(LFTPRINTFDIR) clean

$(OBJDIR)%.o: %.c
	@mkdir -p '$(@D)'
	@$(CC) $(INCLUDE) -c $< -o $@
	@printf "\r\e[?25l\e[Jcompiling \e[32m$(notdir $^)\e[0m"

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LFTDIR) fclean
	@$(MAKE) -C $(LFTPRINTFDIR) fclean

fclean: clean
	@rm -f $(NAME)

re: fclean all
