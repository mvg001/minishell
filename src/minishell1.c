/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:07:17 by mvassall          #+#    #+#             */
/*   Updated: 2025/05/29 18:59:15 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "hmap.h"
#include "minishell.h"
#include "libft.h"

t_result split_key_value(char *env, t_entry *entry)
{
    char *delim;

    if (env == NULL || entry == NULL)
        return (OP_INVALID);
    delim = ft_strchr(env, '=');
    if (delim == NULL)
        return (OP_FAILED);
    entry->key = ft_substr(env, 0, delim - env);
    if (entry->key == NULL)
        return (OP_FAILED);
    entry->value = ft_strdup(delim + 1);
    if (entry->value == NULL)
    {
        free(entry->key);
        return (OP_FAILED);
    }
    return (OP_OK);
}

t_hmap  *load_env_vars(char **envp)
{
    int count;
    t_hmap  *vars;
    t_entry e;

    if (envp == NULL)
        return (NULL);
    count = ft_split_count(envp);
    if (count <= 0)
        return (NULL);
    vars = hmap_create(count * 2, default_hash_func);
    if (vars == NULL)
        return (NULL);
    while (*envp != NULL)
    {
        if (split_key_value(*envp++, &e) == OP_OK)
        {
            hmap_put(vars, e.key, e.value);
            free(e.key);
            free(e.value);
        }
    }
    return (vars);
}

t_minishell *minishell_init(char **envp)
{
    t_minishell *ctx;

    if (envp == NULL)
        return NULL;
    ctx = ft_calloc(1, sizeof(t_minishell));
    if (ctx == NULL)
        return (NULL);
    ctx->last_status = 0;
    ctx->vars = load_env_vars(envp);
    if (ctx->vars == NULL)
    {
        free(ctx);
        return (NULL);
    }
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

int    proc_line(t_minishell *ctx, char *line)
{
    if (ctx == NULL || line == NULL)
    {
        ft_dprintf(2, "INVALID INPUT\n");
        return (1);
    }
    
    return (0);
}