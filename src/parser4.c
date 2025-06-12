/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:09:15 by user1             #+#    #+#             */
/*   Updated: 2025/06/12 09:39:14 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include "libft.h"
#include "parser.h"
#include <complex.h>

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
    if (value != NULL)
    {
        ps_append_cw_string(ps, value);
        free(value);
    }
    free(ps->key);
    ps->key = NULL;
    return (OP_OK);
}

t_result expand_word_4(t_ps *ps, t_minishell *ctx)
{
    (void)ctx;
    if (*ps->cchar == '\'')
        return (ps->state = 1, ps_append_cw_char(ps, '\''));
    return (ps_append_cw_char(ps, *ps->cchar));        
}

t_result expand_word_5(t_ps *ps, t_minishell *ctx)
{
    (void)ctx;
    if (*ps->cchar == '$')
        return (ps->state = 6, ps->key = NULL, OP_OK);
    else if (*ps->cchar == '"')
        return (ps->state = 1, ps_append_cw_char(ps, '"'));
    return (ps_append_cw_char(ps, *ps->cchar));
}

t_result expand_word_6(t_ps *ps, t_minishell *ctx)
{
    char    *ls_str;

    if (*ps->cchar == '_' || ft_isalpha(*ps->cchar))
    {
        ps->state = 7;
        ps->key = append_char(ps->key, *ps->cchar);
        return (OP_OK);
    }
    else if (*ps->cchar == '?')
    {
        ps->state = 5;
        ls_str = ft_itoa(ctx->last_status);
        ps_append_cw_string(ps, ls_str);
        free(ls_str);
        return (OP_OK);
    }
    ps->cchar--;
    return (ps_append_cw_char(ps, '$'));
}

t_result expand_word_7(t_ps *ps, t_minishell *ctx)
{
    char    *value;

    if (*ps->cchar == '_' || ft_isalnum(*ps->cchar))
    {
        ps->key = append_char(ps->key, *ps->cchar);
        return (OP_OK);
    }
    ps->state = 5;
    ps->cchar--;
    value = hmap_lookup(ctx->vars, ps->key);
    if (value != NULL)
    {
        ps_append_cw_string(ps, value);
        free(value);
    }
    free(ps->key);
    ps->key = NULL;
    return (OP_OK);
}
