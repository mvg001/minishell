/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:47:36 by user1             #+#    #+#             */
/*   Updated: 2025/06/14 12:45:21 by user1            ###   ########.fr       */
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
	t_ps *ps;
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

static void loop_states_tokenizer(t_ps *ps)
{
	t_result (*state_func[])(t_ps *) = {
		NULL,
		tokenizer_1,
		tokenizer_2,
		tokenizer_3,
		tokenizer_4,
		tokenizer_5,
};
	while (ps->state > 0)
	{
		state_func[ps->state](ps);
		ps->cchar++;
	}
}

t_list *parser_tokenizer(t_minishell *ctx, char *line)
{
	t_ps	*ps;

	if (ctx == NULL || line == NULL)
		return (NULL);
	ps = ps_create(line, 1);
	if (ps == NULL)
		return (NULL);
	loop_states_tokenizer(ps);
	if (ps->state < 0)
	{
		ft_lstclear(&ps->words, free);
		ft_dprintf(2, "* Invalid input\n");
		ps_destroy(&ps);
		return (NULL);
	}
	return (ps_destroy(&ps));
}

t_list	*minishell_parse_line(t_minishell *ctx, char *line)
{
	t_list		*words;
	t_list		*output;

	if (ctx == NULL || line == NULL)
		return (NULL);
	words = parser_tokenizer(ctx, line);
	parser_print_words("tokenizer output words", words);
	output = expand_words(words, ctx);
	parser_print_words("expand_words output words", output);
	if (words != NULL)
		ft_lstclear(&words, free);
	return (output);
}
