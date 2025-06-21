/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:49:19 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/21 19:45:50 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include "libft.h"
#include "minishell.h"

static void loop_states_parser_pipeline(t_pp *pps)
{
    t_result (*state_func[])(t_pp *, char *) = {
        NULL,
        parse_pipe1,
        parse_pipe2,
        parse_pipe3,
        parse_pipe4,
        parse_pipe5,
};
    while (pps->state > 0)
    {
        state_func[pps->state](pps, pps->tokens[pps->itk]);
        pps->itk++;
    }
}
t_command   **get_cmd_array_from_list(t_list *cmd_lst)
{
    t_command   **cmds;
    int         i;

    if (cmd_lst == NULL)
        return (NULL);
    cmds = ft_calloc(ft_lstsize(cmd_lst) + 1, sizeof(t_command *));
    i = 0;
    while (cmd_lst != NULL)
    {
        cmds[i++] = cmd_lst->content;
        cmd_lst = cmd_lst->next;
    }
    return (cmds);
}
static t_result add_new_vars(t_hmap *hm, t_list **new_vars)
{
    t_entry *e;
    t_list *vars;

    if (new_vars == NULL)
        return (OP_FAILED);
    vars = *new_vars;
    while (vars != NULL)
    {
        e = hmap_create_entry_from_str(vars->content, 0);
        hmap_put_entry(hm, e->key, e->value, 0);
        entry_destroy(e);
        vars = vars->next;
    }
    ft_lstclear(new_vars, free);
    return (OP_OK);
}

t_pipeline *minishell_parse_tokens(t_minishell *ctx, char **tokens)
{
    t_pp        *pps;
    t_pipeline  *pipeline;

    if (ctx == NULL || tokens == NULL)
        return (NULL);
    pps = msh_create_pp_state();
    if (pps == NULL)
        return (NULL);
    pps->tokens = tokens;
    pps->itk = 0;
    loop_states_parser_pipeline(pps);
    if (pps->state != 0)
    {
        ft_dprintf(2, "minishell: syntax error near unexpected token `newline'\n");
        ctx->last_status = 2;
        msh_destroy_pp_state(&pps);
        return (NULL);
    }
    if (ft_lstsize(pps->vars) > 0 && add_new_vars(ctx->vars, &pps->vars) != OP_OK)
        return (NULL);
    pipeline = msh_create_pipeline();
    if (pipeline == NULL)
    {
        msh_destroy_pp_state(&pps);
        return (NULL);
    }
    pipeline->envp = hmap_to_envp(ctx->vars);
    pipeline->n_commands = ft_lstsize(pps->cmds);
    pipeline->commands = get_cmd_array_from_list(pps->cmds);
    ft_lstclean(&pps->cmds, NULL);
    msh_destroy_pp_state(&pps);
    if (msh_process_pipeline_heredocs(ctx, pipeline) != OP_OK)
        msh_destroy_pipeline(pipeline);
    return (pipeline);
}
