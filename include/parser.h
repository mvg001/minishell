/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:44:54 by user1             #+#    #+#             */
/*   Updated: 2025/06/10 13:46:28 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
#include "hmap.h"
# include "libft.h"

typedef enum e_ttype
{
    TT_ERROR,
    TT_WORD,
    TT_OPERATOR,
    TT_ASSIGNMENT,
} t_ttype;

typedef struct s_token
{
    t_ttype token_type;
    char *string;
} t_token;

typedef struct s_parser_i
{
    int     state;
	t_list	*words;
	char	*cw;
	char	*key;
	char	*cchar;
} t_parser_i;

char *append_char(char *w, char c);
t_result append_cw_char(t_parser_i *pi, char c);
t_result append_cw_string(t_parser_i *pi, char *str);
t_result append_word(t_parser_i *pi);
t_result tokenizer_1(t_parser_i *pi);
t_result tokenizer_2(t_parser_i *pi);
t_result tokenizer_3(t_parser_i *pi);
t_result tokenizer_4(t_parser_i *pi);
t_result tokenizer_5(t_parser_i *pi);
#endif
