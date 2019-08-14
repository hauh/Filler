# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smorty <smorty@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/12 16:55:12 by smorty            #+#    #+#              #
#    Updated: 2019/08/14 16:26:49 by smorty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := smorty.filler

SRCSFILES := main.c init.c read_input.c heat_map.c solve.c utility.c

SRCDIR := srcs/

OBJDIR := $(SRCDIR)obj/

LFTDIR := $(SRCDIR)libft/

LFT := $(LFTDIR)libft.a

INCLUDE := include

SRCS := $(addprefix $(SRCDIR), $(SRCSFILES))

OBJ := $(SRCS:%.c=$(OBJDIR)%.o)

CC := gcc -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(LFT) $(OBJ)
	@$(CC) $^ -o $@
	@printf "\r\e[J\e[32m$@\e[0m done!\n\e[?25h"

$(LFT):
	@$(MAKE) -C $(LFTDIR)
	@$(MAKE) -C $(LFTDIR) clean

$(OBJDIR)%.o: %.c
	@mkdir -p '$(@D)'
	@$(CC) -I$(INCLUDE) -I./$(LFTDIR) -c $< -o $@
	@printf "\r\e[?25l\e[Jcompiling \e[32m$(notdir $^)\e[0m"

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LFTDIR) fclean

fclean: clean
	@rm -f $(NAME)

re: fclean all
