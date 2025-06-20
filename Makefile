# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvassall <mvassall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 11:05:02 by user1             #+#    #+#              #
#    Updated: 2025/06/20 18:17:47 by mvassall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
CFLAGS := -Wall -Werror -Wextra
RM := /bin/rm -f
SRC_DIRS := ./src
BUILD_DIR := ./build

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

NAME = minishell

.PHONY: all clean fclean re

all: $(NAME)

show:
	echo $(OBJS)

$(NAME): $(OBJS) libft/libft.a
	$(CC) -o $(NAME) $(OBJS) -L./libft/ -lft -lreadline

$(OBJS): libft/libft.h include/hmap.h include/minishell.h include/parser.h

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I./libft/ -I./include -o $@ -c $<

libft/libft.a:
	cd libft && $(MAKE) all

clean:
	$(RM) $(OBJS)
	cd libft && $(MAKE) clean

fclean: clean
	$(RM) $(NAME) 
	cd libft && $(MAKE) fclean

re: fclean all
