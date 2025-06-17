/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:31:30 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/17 17:51:07 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"

t_pipeline *minishell_parse_words(t_minishell *ctx, t_list *words)
{

    t_pipeline  *pipeline;

    if (ctx == NULL || words == NULL)
        return (NULL);
    pipeline = msh_create_pipeline();
    if (pipeline == NULL)
        return (NULL);
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