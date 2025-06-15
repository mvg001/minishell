/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:27:13 by user1             #+#    #+#             */
/*   Updated: 2025/06/15 13:25:04 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include <unistd.h>

static void	expand_word_loop(t_ps *ps, t_minishell *ctx)
{
	t_result (*state_func[])(t_ps *, t_minishell *) = {
	NULL,
	expand_word_1,
	expand_word_2,
	expand_word_3,
	expand_word_4,
	expand_word_5,
	expand_word_6,
	expand_word_7,
};
	while (ps->state > 0)
	{
		state_func[ps->state](ps, ctx);
		ps->cchar++;
	}
}

char	*expand_word(char *input_txt, t_minishell *ctx)
{
	t_ps	*ps;
	char	*output;

	ps = ps_create(input_txt, 1);
	if (ps == NULL)
		return (NULL);
	expand_word_loop(ps, ctx);
	output = NULL;
	if (ps->cw != NULL)
	{
		output = ft_strdup(ps->cw);
	}
	ps_destroy(&ps);
	return (output);
}

t_result	expand_word_1(t_ps *ps, t_minishell *ctx)
{
	(void)ctx;
	if (*ps->cchar == '$')
		return (ps->state = 2, ps->key = NULL, OP_OK);
	else if (*ps->cchar == '\0')
		return (ps->state = 0, OP_OK);
	else if (*ps->cchar == '\'')
		return (ps->state = 4, ps_append_cw_char(ps, '\''));
	else if (*ps->cchar == '"')
		return (ps->state = 5, ps_append_cw_char(ps, '"'));
	return (ps_append_cw_char(ps, *ps->cchar), OP_OK);
}

t_result	expand_word_2(t_ps *ps, t_minishell *ctx)
{
	char	*ls_str;

	if (*ps->cchar == '?')
	{
		ps->state = 1;
		ls_str = ft_itoa(ctx->last_status);
		ps_append_cw_string(ps, ls_str);
		free(ls_str);
		return (OP_OK);
	}
	else if (*ps->cchar == '_' || ft_isalpha(*ps->cchar))
	{
		ps->key = append_char(NULL, *ps->cchar);
		return (ps->state = 3, OP_OK);
	}
	ps->cchar--;
	return (ps->state = 1, ps_append_cw_char(ps, '$'));
}

t_result expand_word_3(t_ps *ps, t_minishell *ctx)
{
    char *value;

    if (*ps->cchar == '_' || ft_isalnum(*ps->cchar))
    {
        ps->key = append_char(ps->key, *ps->cchar);
        return (OP_OK);
    }
    ps->state = 1;
    ps->cchar--;
    value = hmap_lookup(ctx->vars, ps->key);
    if (value == NULL)
        value = ft_strdup("");
    else
        substitute_quotes_dc1_dc2(value);
    ps_append_cw_string(ps, value);
    free(value);
    free(ps->key);
    ps->key = NULL;
    return (OP_OK);
}
