/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:47:36 by user1             #+#    #+#             */
/*   Updated: 2025/06/17 14:34:51 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "libft.h"
#include "parser.h"

t_ps	*ps_create(char *input_txt, int initial_state)
{
	t_ps	*ps;

	if (input_txt == NULL)
		return (NULL);
	ps = ft_calloc(1, sizeof(t_ps));
	if (ps == NULL)
		return (NULL);
	ps->cw = NULL;
	ps->words = NULL;
	ps->cchar = input_txt;
	ps->key = NULL;
	ps->state = initial_state;
	return (ps);
}

t_list	*ps_destroy(t_ps **parser_state)
{
	t_ps	*ps;
	t_list	*words_saved;

	if (parser_state == NULL)
		return (NULL);
	ps = *parser_state;
	if (ps == NULL)
		return (NULL);
	if (ps->key != NULL)
		free(ps->key);
	if (ps->cw != NULL)
		free(ps->cw);
	words_saved = ps->words;
	free(ps);
	*parser_state = NULL;
	return (words_saved);
}

// parser_print_words("tokenizer output words", words);
// parser_print_words("expand_words output words", exp_words);
t_list	*minishell_parse_line(t_minishell *ctx, char *line)
{
	t_list		*words;
	t_list		*exp_words;
	t_list		*output;

	if (ctx == NULL || line == NULL)
		return (NULL);
	words = parser_tokenizer(ctx, line);
	exp_words = expand_words(words, ctx);
	if (words != NULL)
		ft_lstclear(&words, free);
	output = ft_lstmap(exp_words, cleanup_quotes_dc1_dc2, free);
	if (exp_words != NULL)
		ft_lstclear(&exp_words, free);
	return (output);
}
