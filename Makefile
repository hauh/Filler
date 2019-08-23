# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smorty <smorty@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/12 16:55:12 by smorty            #+#    #+#              #
#    Updated: 2019/08/23 18:18:37 by smorty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := smorty.filler

VISUAL := filler_visual

SRCSFILES := main.c init_bot.c read_input.c heat_map.c solver.c find_move.c shared.c

SRCSFILES_VIS := visualizer.c init_visualizer.c read_input.c shared.c

SRCDIR := srcs/

OBJDIR := $(SRCDIR)obj/

LFTDIR := $(SRCDIR)libft/

LFT := $(LFTDIR)libft.a

LFTPRINTFDIR := $(SRCDIR)ft_printf/

LFTPRINTF := $(LFTPRINTFDIR)libftprintf.a

SDL2 := $(SRCDIR)sdl2/lib/libSDL2-2.0.0.dylib

INCLUDE := -I./srcs/sdl2/include/SDL2 -I./include -I./$(LFTDIR) -I./$(LFTPRINTFDIR)includes/

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
	@$(CC) $^ $(SDL2) -o $@
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

fclean: clean
	@rm -f $(NAME)

re: fclean all
