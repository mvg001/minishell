/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:47:45 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/18 19:28:58 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include "minishell.h"

t_result    pipe1(t_pp *pps)
{
    t_entry *e;
    t_list  *aux;

    if (pps->ctk == NULL)
        return (pps->state = 0, OP_OK);
    pps->op = get_operator_type(pps->ctk->content);
    if (pps->op != OPER_NONE && pps->op != OPER_ERROR)
        return (pps->state = 2, OP_OK);
    e = hmap_create_entry_from_str(pps->ctk->content, 0);
    if (e != NULL)
    {
        aux = ft_lstnew(e);
        if (aux == NULL)
            return (pps->state = -1, OP_FAILED);
        ft_lstadd_back(&pps->vars, aux);
        return (pps->state = 5, OP_OK);
    }
    aux = ft_lstnew(pps->ctk->content);
    if (aux == NULL)
        return (pps->state = -1, OP_FAILED);
    ft_lstadd_back(&pps->args, aux);
    return (pps->state = 3, OP_OK);
}

t_result    pipe2(t_pp *pps)
{
    t_operator opt;

    if (pps->ctk == NULL)
        return (pps->state = -1, OP_OK);
    opt = get_operator_type(pps->ctk->content);
    if (opt != OPER_ERROR && opt != OPER_NONE)
        return (pps->state = -1, OP_OK);
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

t_result    pipe3(t_pp *pps)
{
    char    **av;

    if (pps->ctk == NULL)
    {
        
        pps->ccmd->args = pps->args;
    }
}