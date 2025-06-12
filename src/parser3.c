/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:27:13 by user1             #+#    #+#             */
/*   Updated: 2025/06/12 09:08:50 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"

t_result	tokenizer_5(t_ps *pi)
{
	if (*pi->cchar == '"')
	{
		ps_append_cw_char(pi, '"');
		pi->state = 1;
	}
	else if (*pi->cchar == '\0')
	{
		ft_dprintf(2, "Missing closing double quote\n");
		pi->state = -1;
	}
	else
		ps_append_cw_char(pi, *pi->cchar);
	return (OP_OK);
}

static void	expand_word_loop(t_ps *ps, t_minishell *ctx)
{
	t_result (*state_func[])(t_ps * ps, t_minishell *ctx) = {
	NULL, expand_word_1, expand_word_2, expand_word_3, expand_word_4,
	expand_word_5, expand_word_6
};
	while (ps->state > 0)
	{
		state_func[ps->state](ps, ctx);
		ps->cchar++;
	}
}

t_list	*expand_word(char *input_txt, t_minishell *ctx)
{
	t_ps	*ps;

	if (ft_strchr(input_txt, '$') == NULL)
		return (NULL);
	ps = ps_create(input_txt, 1);
	if (ps == NULL)
		return (NULL);
	expand_word_loop(ps, ctx);
	return (NULL);
}

t_result expand_word_1(t_ps *ps, t_minishell *ctx)
{
	(void)ctx;
	if (*ps->cchar == '$')
		return (ps->state = 2, ps->key = NULL, OP_OK);
	else if (*ps->cchar == '\0')
		return (ps->state = 0, ps_append_word(ps));
	else if (*ps->cchar == '\'')
		return (ps->state = 4, ps_append_cw_char(ps, '\''));
	else if (*ps->cchar == '"')
		return (ps->state = 5, ps_append_cw_char(ps, '"'));
	return (ps_append_cw_char(ps, *ps->cchar), OP_OK);
}

t_result expand_word_2(t_ps *ps, t_minishell *ctx)
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
		return (ps->state = 3, ps_append_cw_char(ps, *ps->cchar));
	ps->cchar--;
	return (ps->state = 1, ps_append_cw_char(ps, '$'));
}
