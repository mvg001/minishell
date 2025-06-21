/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:55:44 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/21 16:39:32 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include "libft.h"
#include "minishell.h"

static t_result append_new_command(t_pp *pps)
{
    char    **argv;
    t_list    *aux;

    ft_dprintf(2, "append_new_command\n");
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
        ft_dprintf(2, "append_new_command return OP_FAILED\n");
        return (OP_FAILED);
    }
    ft_lstadd_back(&pps->cmds, aux);
    pps->ccmd = msh_create_command();
    ft_dprintf(2, "append_new_command return OP_OK\n");
    return (OP_OK);
}

static t_result append_new_arg(t_pp *pps)
{
    t_list  *aux;
    char    *str_dup;

    ft_dprintf(2, "append_new_arg\n");
    if (pps == NULL)
    {
        ft_dprintf(2, "append_new_arg return OP_INVALID\n");
        return (OP_INVALID);
    }
    str_dup = ft_strdup(pps->tokens[pps->itk]);
    if (str_dup == NULL)
    {
        ft_dprintf(2, "append_new_arg return OP_FAILED 1\n");
        return (pps->state = -1, OP_FAILED);
    }
    aux = ft_lstnew(str_dup);
    if (aux == NULL)
    {
        free(str_dup);
        ft_dprintf(2, "append_new_arg return OP_FAILED 2\n");
        return (pps->state = -1, OP_FAILED);
    }
    ft_lstadd_back(&pps->args, aux);
    ft_dprintf(2, "append_new_arg return OP_OK\n");
    return (OP_OK);
}

t_result    parse_pipe3(t_pp *pps, char *ctk)
{
    ft_dprintf(2, "parse_pipe3 cur_tk [%s]\n", ctk);
    if (ctk == NULL)
    {
        if (append_new_command(pps) != OP_OK)
            return (pps->state = -1, OP_FAILED);
        return (pps->state = 0, OP_OK);
    }
    pps->op = get_operator_type(ctk);
    if (pps->op == OPER_PIPE)
        return (pps->state = -1, OP_FAILED);
    if (pps->op != OPER_NONE && pps->op != OPER_ERROR)
        return (pps->state = 4, OP_OK);
    if (append_new_arg(pps) != OP_OK)
        return (pps->state = -1, OP_FAILED);
    return (pps->state = 5, OP_OK);
}

t_result    parse_pipe5(t_pp *pps, char *ctk)
{
    t_operator  op;

    ft_dprintf(2, "parse_pipe5 cur_tk [%s]\n", ctk);
    op = get_operator_type(ctk);
    if (op == OPER_PIPE)
    {
        if (append_new_command(pps) != OP_OK)
            return (pps->state = -1, OP_FAILED);
        return (pps->state = 3, OP_OK);
    }
    pps->itk--;
    return (pps->state = 3, OP_OK);
}
