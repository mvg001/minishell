/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:47:45 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/19 20:00:50 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include "minishell.h"

static t_result append_new_command(t_pp *pps)
{
    char    **argv;
    t_list    *aux;

    if (pps == NULL)
        return (OP_FAILED);
    argv = ft_lst_to_argv(pps->args);
    ft_lstclear(&pps->args, free);
    pps->ccmd->args = argv;
    aux = ft_lstnew(pps->ccmd);
    if (aux == NULL)
    {
        ft_dispose_split(argv);
        pps->state = -1;
        return (OP_FAILED);
    }
    ft_lstadd_back(&pps->cmds, aux);
    pps->ccmd = NULL;
    return (OP_OK);
}

static t_result append_new_word(t_pp *pps)
{
    t_list *aux;

    if (pps == NULL)
        return (OP_INVALID);
    aux = ft_lstnew(pps->ctk->content);
    if (aux == NULL)
        return (pps->state = -1, OP_FAILED);
    ft_lstadd_back(&pps->args, aux);
    return (OP_OK);
}

t_result    pipe1(t_pp *pps)
{
    t_entry *e;
    t_list  *aux;

    if (pps->ctk == NULL)
        return (pps->state = 0, OP_OK);
    if (pps->ccmd == NULL)
        pps->ccmd = msh_create_command();
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
    if (append_new_word(pps) != OP_OK)
        return (OP_FAILED);
    return (pps->state = 3, OP_OK);
}



t_result    pipe3(t_pp *pps)
{
    pps->op = get_operator_type(pps->ctk->content);
    if (pps->op != OPER_NONE && pps->op != OPER_ERROR && pps->op != OPER_PIPE)
        return (pps->state = 4, OP_OK);
    if (pps->ctk == NULL || pps->op == OPER_PIPE)
    {
        if (append_new_command(pps) != OP_OK)
            return (pps->state = -1, OP_FAILED);
        if (pps->ctk == NULL)
            return (pps->state = 0, OP_OK);
        return (pps->op = OPER_NONE, pps->state = 1, OP_OK);
    }
    if (append_new_word(pps) != OP_OK)
        return (OP_FAILED);
    return (pps->state = 3, OP_OK);
}


