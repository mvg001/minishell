/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:44:54 by user1             #+#    #+#             */
/*   Updated: 2025/06/12 09:00:19 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "hmap.h"
# include "libft.h"
# include "minishell.h"

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

// parser state
typedef struct s_ps
{
    int     state;
	t_list	*words;
	char	*cw;
	char	*key;
	char	*cchar;
} t_ps;

char *append_char(char *w, char c);
t_ps	*ps_create(char *input_txt, int initial_state);
void    ps_destroy(t_ps **ps);

t_result ps_append_cw_char(t_ps *ps, char c);
t_result ps_append_cw_string(t_ps *ps, char *str);
t_result ps_append_word(t_ps *ps);
t_result tokenizer_1(t_ps *ps);
t_result tokenizer_2(t_ps *ps);
t_result tokenizer_3(t_ps *ps);
t_result tokenizer_4(t_ps *ps);
t_result tokenizer_5(t_ps *ps);
int count_pipe_operators(t_list *words);
t_list  *split_simple_commands(t_list *words);

t_list  *expand_word(char *input_txt, t_minishell *ctx);
t_result expand_word_1(t_ps *ps, t_minishell *ctx);
t_result expand_word_2(t_ps *ps, t_minishell *ctx);
t_result expand_word_3(t_ps *ps, t_minishell *ctx);
t_result expand_word_4(t_ps *ps, t_minishell *ctx);
t_result expand_word_5(t_ps *ps, t_minishell *ctx);
t_result expand_word_6(t_ps *ps, t_minishell *ctx);
#endif
