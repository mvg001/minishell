/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:31:30 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/10 13:47:15 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_string(void *p)
{
    ft_printf("[%s]\n", (char *)p);
}

t_pipeline *minishell_parse_words(t_minishell *ctx, t_list *words)
{
    t_pipeline  *pipeline;

    if (ctx == NULL || words == NULL)
        return (NULL);
    pipeline = NULL; // TODO
    ft_lstiter(words, print_string);
    return (pipeline);
}

int			minishell_execute(t_minishell *ctx, t_pipeline *cmds)
{
    // TODO!!!!!!
    (void)ctx;
    (void)cmds;
    return (0);
}