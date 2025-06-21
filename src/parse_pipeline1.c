/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:47:45 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/21 17:11:05 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include "libft.h"
#include "minishell.h"

t_pp    *msh_create_pp_state()
{
    t_pp    *pps;

    pps = ft_calloc(1, sizeof(t_pp));
    if (pps == NULL)
        return (NULL);
    pps->state = 1;
    pps->op = OPER_NONE;
    return (pps);
}

void    msh_destroy_pp_state(t_pp **p_pps)
{
    t_pp    *pps;

    ft_dprintf(2, "msh_destroy_pp_state\n");
    if (p_pps == NULL || *p_pps == NULL)
        return ;
    pps = *p_pps;
    if (pps->cmds != NULL)
        ft_lstclear(&pps->cmds, free);
    ft_dprintf(2, "msh_destroy_pp_state cmds freed\n");
    if (pps->vars != NULL)
        ft_lstclear(&pps->vars, free);
    ft_dprintf(2, "msh_destroy_pp_state vars freed\n");
    if (pps->args != NULL)
        ft_lstclear(&pps->args, free);
    ft_dprintf(2, "msh_destroy_pp_state args freed\n");
    if (pps->ccmd != NULL)
        msh_destroy_command(&pps->ccmd);
    ft_dprintf(2, "msh_destroy_pp_state ccmd freed\n");
    free(pps);
    pps = NULL;
    ft_dprintf(2, "msh_destroy_pp_state return\n");
}

t_result    parse_pipe1(t_pp *pps, char *ctk)
{
    t_entry *e;
    t_list  *aux;
    char    *dup;

    ft_dprintf(2, "parse_pipe1 cur_tk [%s]\n", ctk);
    e = hmap_create_entry_from_str(ctk, 0);
    if (e != NULL)
    {
        entry_destroy(e);
        dup = ft_strdup(ctk);
        if (dup == NULL)
            return (pps->state = -1, OP_FAILED);
        aux = ft_lstnew(dup);
        if (aux == NULL)
            return (free(dup), pps->state = -1, OP_FAILED);
        ft_lstadd_back(&pps->vars, aux);
        return (pps->state = 2, OP_OK);
    }
    pps->itk--;
    if (pps->ccmd == NULL)
        pps->ccmd = msh_create_command();
    return (pps->state = 3, OP_OK);
}
t_result    parse_pipe2(t_pp *pps, char *ctk)
{
    t_entry *e;
    t_list  *aux;
    char    *dup;

    ft_dprintf(2, "parse_pipe2 cur_tk [%s]\n", ctk);
    if (ctk == NULL)
        return (pps->state = 0, OP_OK);
    e = hmap_create_entry_from_str(ctk, 0);
    if (e == NULL)
    {
        ft_dprintf(2, "minishell: syntax error near unexpected token `newline'\n");
        return (pps->state = -1, OP_FAILED);
    }
    entry_destroy(e);
    dup = ft_strdup(ctk);
    if (dup == NULL)
        return (pps->state = -1, OP_FAILED);
    aux = ft_lstnew(dup);
    if (aux == NULL)
    {
        free(dup);
        return (pps->state = -1, OP_FAILED);
    }
    ft_lstadd_back(&pps->vars, aux);
    return (OP_OK);    
}

t_result    parse_pipe4(t_pp *pps, char *ctk)
{
    t_operator  op;
    char        *str_dup;

    ft_dprintf(2, "parse_pipe4 cur_tk [%s]\n", ctk);
    if (ctk == NULL)
        return (pps->state = -1, OP_FAILED);
    op = get_operator_type(ctk);
    if (op != OPER_ERROR && op != OPER_NONE)
        return (pps->state = -1, OP_FAILED);
    str_dup = ft_strdup(ctk);
    if (str_dup == NULL)
        return (pps->state = -1, OP_FAILED);
    if (pps->op == OPER_LT || pps->op == OPER_LT_LT)
    {
        pps->ccmd->input_file = str_dup;
        pps->ccmd->is_here_doc = pps->op == OPER_LT_LT;
    }
    if (pps->op == OPER_GT || pps->op == OPER_GT_GT)
    {
        pps->ccmd->output_file = str_dup;
        pps->ccmd->append_output = pps->op == OPER_GT_GT;
    }
    pps->op = OPER_NONE;
    return (pps->state = 3, OP_OK);
}
