/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:44:54 by user1             #+#    #+#             */
/*   Updated: 2025/06/18 15:40:30 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "hmap.h"
# include "libft.h"
# include "minishell.h"

// parser state
typedef struct s_ps
{
	int		state;
	t_list	*words;
	char	*cw;
	char	*key;
	char	*cchar;
}	t_ps;

void		parser_print_words(char *title, t_list *words);
char		*append_char(char *w, char c);
t_ps		*ps_create(char *input_txt, int initial_state);
t_list		*ps_destroy(t_ps **parser_state);
void		parser_print_ps(t_ps *ps);

# define DC1 '\x11'
# define DC2 '\x12'

void		substitute_quotes_dc1_dc2(char *str);
void		substitute_dc1_dc2_quotes(char *str);
void		*cleanup_quotes_dc1_dc2(void *ptr);

t_result	ps_append_cw_char(t_ps *ps, char c);
t_result	ps_append_cw_string(t_ps *ps, char *str);
t_result	ps_append_word(t_ps *ps);
t_list		*parser_tokenizer(t_minishell *ctx, char *line);
t_result	tokenizer_1(t_ps *ps);
t_result	tokenizer_2(t_ps *ps);
t_result	tokenizer_3(t_ps *ps);
t_result	tokenizer_4(t_ps *ps);
t_result	tokenizer_5(t_ps *ps);
int			count_pipe_operators(t_list *words);
t_list		*split_simple_commands(t_list *words);

t_list		*expand_words(t_list *words, t_minishell *ctx);
char		*expand_word(char *input_txt, t_minishell *ctx);
t_result	expand_word_1(t_ps *ps, t_minishell *ctx);
t_result	expand_word_2(t_ps *ps, t_minishell *ctx);
t_result	expand_word_3(t_ps *ps, t_minishell *ctx);
t_result	expand_word_4(t_ps *ps, t_minishell *ctx);
t_result	expand_word_5(t_ps *ps, t_minishell *ctx);
t_result	expand_word_6(t_ps *ps, t_minishell *ctx);
t_result	expand_word_7(t_ps *ps, t_minishell *ctx);
#endif
