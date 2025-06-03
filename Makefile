# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvassall <mvassall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 11:05:02 by user1             #+#    #+#              #
#    Updated: 2025/06/03 17:58:48 by mvassall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = /bin/rm -f

OBJS = src/hmap1.o src/hmap2.o src/hmap3.o src/main.o src/minishell1.o \
src/parser1.o src/minishell2.o

NAME = minishell

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(CC) -o $(NAME) $(OBJS) -Llib/libft/ -lft -lreadline

$(OBJS): lib/libft/libft.h include/hmap.h include/minishell.h

%.o: %.c
	$(CC) $(CFLAGS) -Ilib/libft/ -Iinclude -o $@ -c $<

libft/libft.a:
	cd lib/libft && $(MAKE) all

clean:
	$(RM) $(OBJS) $(NAME)
	cd lib/libft && $(MAKE) clean

fclean: clean
	$(RM) $(NAME) 
	cd lib/libft && $(MAKE) fclean

re: fclean all
