# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvassall <mvassall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 11:05:02 by user1             #+#    #+#              #
#    Updated: 2025/06/06 15:22:28 by mvassall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = /bin/rm -f

OBJS = ft_atoi.o ft_bzero.o ft_calloc.o ft_itoa.o ft_memchr.o \
ft_memcmp.o ft_memcpy.o ft_memmove.o ft_memset.o ft_putstr_fd.o ft_split.o \
ft_strchr.o ft_strcmp.o ft_strdup.o ft_striteri.o ft_strjoin.o \
ft_strlcat.o ft_strlcpy.o ft_strlen.o ft_strmapi.o ft_strncmp.o \
ft_strnstr.o ft_strrchr.o ft_strtrim.o ft_substr.o ft_toupper_tolower.o \
ft_isalnum.o ft_isalpha.o ft_isascii.o ft_isprint.o ft_isdigit.o \
ft_lstadd_back_bonus.o ft_lstadd_front_bonus.o ft_lstclear_bonus.o \
ft_lstdelone_bonus.o ft_lstiter_bonus.o ft_lstlast_bonus.o ft_lstmap_bonus.o \
ft_lstnew_bonus.o ft_lstsize_bonus.o \
ft_printf.o ft_c_conversion.o ft_d_conversion.o ft_p_conversion.o \
ft_s_conversion.o ft_u_conversion.o ft_x_conversion.o ft_isspace.o \
ft_atol.o gnl.o gnl_utils_1.o gnl_utils_2.o ft_split_1.o ft_is_number.o

NAME = libft.a

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJS): libft.h

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
