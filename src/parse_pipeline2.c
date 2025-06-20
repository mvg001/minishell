/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:55:44 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/19 20:00:53 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include "minishell.h"

t_result    pipe2(t_pp *pps)
{
    t_operator opt;

    if (pps->ctk == NULL)
        return (pps->state = -1, OP_FAILED);
    opt = get_operator_type(pps->ctk->content);
    if (opt != OPER_ERROR && opt != OPER_NONE)
        return (pps->state = -1, OP_FAILED);
    pps->state = 1;
    if (pps->op == OPER_GT || pps->op == OPER_GT_GT)
    {
        pps->ccmd->output_file = ft_strdup(pps->ctk->content);
        pps->ccmd->append_output = (pps->op == OPER_GT_GT);
        pps->op = OPER_NONE;
        return (pps->op = OPER_NONE, OP_OK);
    }
    if (pps->op == OPER_LT || pps->op == OPER_LT_LT)
    {
        pps->ccmd->input_file = ft_strdup(pps->ctk->content);
        pps->ccmd->is_here_doc = (pps->op == OPER_LT_LT);
        pps->op = OPER_NONE;
        return (OP_OK);
    }
    pps->state = -1;
    return (OP_FAILED);
}

t_result pipe4(t_pp *pps)
{
    t_operator opt;

    if (pps->ctk == NULL)
        return (pps->state = -1, OP_FAILED);
    opt = get_operator_type(pps->ctk->content);
    if (opt != OPER_ERROR && opt != OPER_NONE)
        return (pps->state = -1, OP_FAILED);
    pps->state = 3;
    if (pps->op == OPER_GT || pps->op == OPER_GT_GT)
    {
        pps->ccmd->output_file = ft_strdup(pps->ctk->content);
        pps->ccmd->append_output = (pps->op == OPER_GT_GT);
        pps->op = OPER_NONE;
        return (pps->op = OPER_NONE, OP_OK);
    }
    if (pps->op == OPER_LT || pps->op == OPER_LT_LT)
    {
        pps->ccmd->input_file = ft_strdup(pps->ctk->content);
        pps->ccmd->is_here_doc = (pps->op == OPER_LT_LT);
        pps->op = OPER_NONE;
        return (OP_OK);
    }
    pps->state = -1;
    return (OP_FAILED);
}

t_result    pipe5(t_pp *pps)
{
    t_entry *e;
    t_list  *aux;

    e = hmap_create_entry_from_str(pps->ctk->content, 0);
    if (e != NULL)
    {
        aux = ft_lstnew(e);
        if (aux == NULL)
            return (pps->state = -1, OP_FAILED);
        ft_lstadd_back(&pps->vars, aux);
        return (pps->state = 5, OP_OK);
    }
    if (pps->ctk == NULL)
        return (pps->state = 0, OP_OK);
    return (pps->state = -1, OP_FAILED);    
}
