/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:27:13 by user1             #+#    #+#             */
/*   Updated: 2025/06/11 17:46:00 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include "libft.h"
#include "parser.h"

t_result	tokenizer_5(t_ps *pi)
{
	if (*pi->cchar == '"')
	{
		pi_append_cw_char(pi, '"');
		pi->state = 1;
	}
	else if (*pi->cchar == '\0')
	{
		ft_dprintf(2, "Missing closing double quote\n");
		pi->state = -1;
	}
	else
		pi_append_cw_char(pi, *pi->cchar);
	return (OP_OK);
}

static void	expand_word_loop(t_ps *ps, t_hmap *vars)
{
	t_result (*state_func[])(t_ps * ps, t_hmap * vars) = {
	NULL, expand_word_1, expand_word_2, expand_word_3, expand_word_4,
	expand_word_5, expand_word_6
};
	while (ps->state > 0)
	{
		state_func[ps->state](ps, vars);
		ps->cchar++;
	}
}

t_list	*expand_word(char *input_txt, t_hmap *vars)
{
	t_ps	*ps;

	if (ft_strchr(input_txt, '$') == NULL)
		return (NULL);
	ps = ps_create(input_txt, 1);
	if (ps == NULL)
		return (NULL);
	expand_word_loop(ps, vars);
	return (NULL);
}

t_result expand_word_1(t_ps *ps, t_hmap *vars)
{
	
	return (OP_OK);
}
