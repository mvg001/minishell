/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:31:30 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/14 12:11:37 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_pipeline *minishell_parse_words(t_minishell *ctx, t_list *words)
{
    t_pipeline  *pipeline;

    if (ctx == NULL || words == NULL)
        return (NULL);
    pipeline = NULL; // TODO
    parser_print_words("minishell_parse_words:", words);
    return (pipeline);
}

int			minishell_execute(t_minishell *ctx, t_pipeline *cmds)
{
    // TODO!!!!!!
    (void)ctx;
    (void)cmds;
    return (0);
}