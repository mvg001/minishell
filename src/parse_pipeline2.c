/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:55:44 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/20 18:48:44 by mvassall         ###   ########.fr       */
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
    argv = ft_lst_to_argv(pps->args, 0);
    ft_lstclean(&pps->args, NULL);
    pps->ccmd->args = argv;
    aux = ft_lstnew(pps->ccmd);
    if (aux == NULL)
    {
        ft_dispose_split(argv);
        pps->state = -1;
        return (OP_FAILED);
    }
    ft_lstadd_back(&pps->cmds, aux);
    pps->ccmd = msh_create_command();
    return (OP_OK);
}

static t_result append_new_word(t_pp *pps)
{
    t_list *aux;

    if (pps == NULL)
        return (OP_INVALID);
    aux = ft_lstnew(pps->cur_tk);
    if (aux == NULL)
        return (pps->state = -1, OP_FAILED);
    ft_lstadd_back(&pps->args, aux);
    return (OP_OK);
}

t_result    parse_pipe3(t_pp *pps)
{
    ft_dprintf(2, "parse_pipe3 cur_tk [%s]\n", pps->cur_tk);
    if (pps->cur_tk == NULL)
    {
        if (append_new_command(pps) != OP_OK)
            return (pps->state = -1, OP_FAILED);
        return (pps->state = 0, OP_OK);
    }
    pps->op = get_operator_type(pps->cur_tk);
    if (pps->op == OPER_PIPE)
        return (pps->state = -1, OP_FAILED);
    if (pps->op != OPER_NONE && pps->op != OPER_ERROR)
        return (pps->state = 4, OP_OK);
    if (append_new_word(pps) != OP_OK)
        return (pps->state = -1, OP_FAILED);
    return (pps->state = 5, OP_OK);
}

t_result    parse_pipe5(t_pp *pps)
{
    t_operator  op;

    ft_dprintf(2, "parse_pipe3 cur_tk [%s]\n", pps->cur_tk);
    op = get_operator_type(pps->cur_tk);
    if (op == OPER_PIPE)
    {
        if (append_new_command(pps) != OP_OK)
            return (pps->state = -1, OP_FAILED);
        return (pps->state = 3, OP_OK);
    }
    pps->cur_tk--;
    return (pps->state = 3, OP_OK);
}
