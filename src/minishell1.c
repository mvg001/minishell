/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:07:17 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/15 20:38:10 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "hmap.h"
#include "minishell.h"
#include "libft.h"

t_minishell *minishell_init(char **envp)
{
    t_minishell *ctx;

    if (envp == NULL)
        return NULL;
    ctx = ft_calloc(1, sizeof(t_minishell));
    if (ctx == NULL)
        return (NULL);
    ctx->vars = load_env_vars(envp);
    if (ctx->vars == NULL)
    {
        free(ctx);
        return (NULL);
    }
    ctx->last_status = 0;
    ctx->pid = ft_getpid();
    ctx->tmp_count = 1;
    return (ctx);
}

t_result minishell_destroy(t_minishell *ctx)
{
    if (ctx == NULL)
        return (OP_INVALID);
    if (ctx->vars != NULL)
        hmap_destroy(ctx->vars);
    free(ctx);
    return (OP_OK);
}

