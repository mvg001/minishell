/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:19:30 by user1             #+#    #+#             */
/*   Updated: 2025/06/20 10:13:32 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
		ft_dprintf(2, "* Invalid input\n");
		ft_lstclear(&ps->words, free);
		ps_destroy(&ps);
		return (NULL);
	}
	return (ps_destroy(&ps));
}

static t_result tokenizer_1a(t_ps *pi)
{
    if (*pi->cchar == '"')
    {
        ps_append_cw_char(pi, '"');
        pi->state = 5;
    }
    else if (*pi->cchar == '\0' || *pi->cchar == '#')
    {
        ps_append_word(pi);
        pi->state = 0;
    }
    else ps_append_cw_char(pi, *pi->cchar);
    return (OP_OK);
}

t_result tokenizer_1(t_ps *pi)
{
    if (pi == NULL)
        return (OP_INVALID);
    if (ft_isspace(*pi->cchar))
        ps_append_word(pi);
    else if (*pi->cchar == '|')
    {
        ps_append_word(pi);
        ps_append_cw_char(pi, '|');
        ps_append_word(pi);
    }
    else if (*pi->cchar == '<')
        pi->state = 2;
    else if (*pi->cchar == '>')
        pi->state = 3;
    else if (*pi->cchar == '\'')
    {
        ps_append_cw_char(pi, '\'');
        pi->state = 4;
    }
    else  return (tokenizer_1a(pi));
    return (OP_OK);
}

t_result tokenizer_2(t_ps *pi)
{
    ps_append_word(pi);
    pi->state = 1;
    if (*pi->cchar == '<')
    {
        ps_append_cw_string(pi, "<<");
        ps_append_word(pi);
    }
    else
    {
        ps_append_cw_char(pi, '<');
        ps_append_word(pi);
        pi->cchar--;
    }
    return (OP_OK);
}