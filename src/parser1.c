/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:47:36 by user1             #+#    #+#             */
/*   Updated: 2025/06/11 17:44:20 by user1            ###   ########.fr       */
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

void	ps_destroy(t_ps **parser_state)
{
	t_ps *ps;

	if (parser_state == NULL)
		return ;
	ps = *parser_state;
	if (ps == NULL)
		return ;
	if (ps->key != NULL)
		free(ps->key);
	if (ps->cw != NULL)
		free(ps->cw);
	free(ps);
	*parser_state = NULL;
}

/* static void loop_states_tokenizer(t_ps *ps)
{
	while (ps->state > 0)
	{
		if (ps->state == 1)
			tokenizer_1(ps);
		else if (ps->state == 2)
			tokenizer_2(ps);
		else if (ps->state == 3)
			tokenizer_3(ps);
		else if (ps->state == 4)
			tokenizer_4(ps);
		else if (ps->state == 5)
			tokenizer_5(ps);
		ps->cchar++;
	}
} */
static void loop_states_tokenizer(t_ps *ps)
{
	t_result (*state_func[])(t_ps *) = {
		NULL, tokenizer_1, tokenizer_2, tokenizer_3, tokenizer_4, tokenizer_5
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
	t_list	*words;

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
	words = ps->words;
	ps_destroy(&ps);
	return (words);
}


t_list	*minishell_parse_line(t_minishell *ctx, char *line)
{
	t_list		*words;

	if (ctx == NULL || line == NULL)
		return (NULL);
	words = parser_tokenizer(ctx, line);
	return (words);
}
