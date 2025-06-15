/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:24:11 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/15 13:31:05 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"


t_result tokenizer_3(t_ps *ps)
{
    ps_append_word(ps);
    ps->state = 1;
    if (*ps->cchar == '>')
    {
        ps_append_cw_string(ps, ">>");
        ps_append_word(ps);
    }
    else
    {
        ps_append_cw_char(ps, '>');
        ps_append_word(ps);
        ps->cchar--;
    }
    return (OP_OK);
}

t_result tokenizer_4(t_ps *ps)
{
    if (*ps->cchar == '\'')
    {
        ps_append_cw_char(ps, '\'');
        ps->state = 1;
    }
    else if (*ps->cchar == '\0')
    {
        ft_dprintf(2, "Missing closing single quote\n");
        ps->state = -1;
    }
    else if (*ps->cchar == '"')
        ps_append_cw_char(ps, DC2);
    else
        ps_append_cw_char(ps, *ps->cchar);
    return (OP_OK);
}

t_result	tokenizer_5(t_ps *ps)
{
	if (*ps->cchar == '"')
	{
		ps_append_cw_char(ps, '"');
		ps->state = 1;
	}
	else if (*ps->cchar == '\0')
	{
		ft_dprintf(2, "Missing closing double quote\n");
		ps->state = -1;
	}
	else if (*ps->cchar == '\'')
		ps_append_cw_char(ps, DC1);
	else
		ps_append_cw_char(ps, *ps->cchar);
	return (OP_OK);
}