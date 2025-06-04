# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvassall <mvassall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 11:05:02 by user1             #+#    #+#              #
#    Updated: 2025/06/04 16:11:11 by mvassall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = /bin/rm -f

SRCS = $(shell find src -name '*.c')
OBJS = $(patsubst %.c,%.o,$(SRCS))

NAME = minishell

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(CC) -o $(NAME) $(OBJS) -L./libft/ -lft -lreadline

$(OBJS): libft/libft.h include/hmap.h include/minishell.h

%.o: %.c
	$(CC) $(CFLAGS) -I./libft/ -I./include -o $@ -c $<

libft/libft.a:
	cd libft && $(MAKE) all

clean:
	$(RM) $(OBJS) $(NAME)
	cd libft && $(MAKE) clean

fclean: clean
	$(RM) $(NAME) 
	cd libft && $(MAKE) fclean

re: fclean all
