# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smorty <smorty@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/28 16:35:09 by smorty            #+#    #+#              #
#    Updated: 2019/10/07 00:37:29 by smorty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := smorty.filler

VISUAL := filler_visual

SRCSFILES := main_player.c init_bot.c heat_map.c solver.c find_move.c

SRCSFILES_VIS := main_visual.c init_visualizer.c read_board.c visualization_loop.c visualize.c render_board.c utility.c 

SRCS_SHARED := read_input.c error.c

SRCS_DIR := src src/filler src/visualizer

LIBS_DIR := src/libs

OBJS := $(SRCSFILES:.c=.o)

OBJS_VIS := $(SRCSFILES_VIS:.c=.o)

OBJS_SHARED := $(SRCS_SHARED:.c=.o)

OBJ_DIR := obj

LFT := libft.a

LFTPRINTF := libftprintf.a

LFT_DIR := src/libs/libft

LFTPRINTF_DIR := src/libs/ft_printf

HEADERS := filler_shared.h filler_player.h filler_visualizer.h libft.h ft_printf.h SDL.h SDL_ttf.h

HEADERS_DIR := include $(LFT_DIR) $(LFTPRINTF_DIR)/includes

HEADERS_SDL_DIR := $(LIBS_DIR)/SDL2.framework/Headers $(LIBS_DIR)/SDL2_ttf.framework/Headers

SDL_LIBS := -Wl,-rpath,$(LIBS_DIR) -F $(LIBS_DIR) -framework SDL2 -framework SDL2_ttf

CC := gcc -Wall -Werror -Wextra

vpath %.c $(SRCS_DIR)
vpath %.o $(OBJ_DIR) $(OBJ_DIR)/$(NAME) $(OBJ_DIR)/$(VISUAL)
vpath %.h $(HEADERS_DIR) $(HEADERS_SDL_DIR)
vpath %.a $(LFT_DIR) $(LFTPRINTF_DIR)

all: $(NAME) $(VISUAL)

$(NAME): $(LFT) $(LFTPRINTF) $(OBJS) $(OBJS_SHARED)
	@$(CC) $(addprefix $(OBJ_DIR)/, $(addprefix $(NAME)/, $(OBJS)) $(OBJS_SHARED)) -lft -L $(LFT_DIR) -lftprintf -L $(LFTPRINTF_DIR) -o $@
	@printf "\r\e[J\e[32m$@\e[0m done!\n\e[?25h"

$(VISUAL): $(LFT) $(OBJS_VIS) $(OBJS_SHARED)
	@$(CC) $(addprefix $(OBJ_DIR)/, $(addprefix $(VISUAL)/, $(OBJS_VIS)) $(OBJS_SHARED)) -lft -L $(LFT_DIR) -lftprintf -L $(LFTPRINTF_DIR) $(SDL_LIBS) -o $@
	@printf "\r\e[J\e[32m$@\e[0m done!\n\e[?25h"

$(OBJS): %.o: %.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)/$(NAME)
	@$(CC) -c $< $(addprefix -I,$(HEADERS_DIR)) -o $(OBJ_DIR)/$(NAME)/$@
	@printf "\r\e[?25l\e[Jcompiling \e[32m$(notdir $<)\e[0m"

$(OBJS_VIS): %.o: %.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)/$(VISUAL)
	@$(CC) -c $< $(addprefix -I,$(HEADERS_DIR) $(HEADERS_SDL_DIR)) -o $(OBJ_DIR)/$(VISUAL)/$@
	@printf "\r\e[?25l\e[Jcompiling \e[32m$(notdir $<)\e[0m"

$(OBJS_SHARED): %.o: %.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $< $(addprefix -I,$(HEADERS_DIR)) -o $(OBJ_DIR)/$@
	@printf "\r\e[?25l\e[Jcompiling \e[32m$(notdir $<)\e[0m"

$(LFT):
	@$(MAKE) -C $(LFT_DIR)
	@$(MAKE) -C $(LFT_DIR) clean

$(LFTPRINTF):
	@$(MAKE) -C $(LFTPRINTF_DIR)
	@$(MAKE) -C $(LFTPRINTF_DIR) clean

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LFT_DIR) fclean
	@$(MAKE) -C $(LFTPRINTF_DIR) fclean

fclean: clean
	@rm -f $(NAME)
	@rm -f $(VISUAL)

re: fclean all
