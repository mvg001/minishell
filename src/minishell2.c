/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:31:30 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/21 15:56:53 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_operator  get_operator_type(char *str)
{
    if (str == NULL)
        return (OPER_ERROR);
    if (ft_strcmp(str, "<") == 0)
        return (OPER_LT);
    if (ft_strcmp(str, ">") == 0)
        return (OPER_GT);
    if (ft_strcmp(str, "<<") == 0)
        return (OPER_LT_LT);
    if (ft_strcmp(str, ">>") == 0)
        return (OPER_GT_GT);
    if (ft_strcmp(str, "|") == 0)
        return (OPER_PIPE);
    return (OPER_NONE);
}

char    **ft_lst_to_argv(t_list *lst, int is_deep_copy)
{
    char    **av;
    int     i;
    char    *aux;

    av = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
    if (av == NULL)
        return (NULL);
    i = 0;
    while (lst != NULL)
    {
        aux = lst->content;
        if (is_deep_copy)
        {
            aux = ft_strdup(lst->content);
            if (aux == NULL)
                return (ft_dispose_split(av));
        }
        av[i++] = aux;
        lst = lst->next;
    }
    return (av);
}

int minishell_execute(t_minishell *ctx, t_pipeline *pipeline)
{
    // TODO!!!!!!
    (void)ctx;
    msh_print_pipeline(2, pipeline);
    return (0);
}