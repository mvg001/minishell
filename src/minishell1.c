/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:07:17 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/21 20:00:21 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "hmap.h"
#include "minishell.h"
#include "libft.h"
#include "parser.h"

char *get_tmp_filename(t_minishell *ctx)
{
    char *n_str;
    char *filename;

    filename = ft_strdup(ctx->tmpfilename_prefix);
    n_str = ft_itoa(ctx->tmp_count++);
    filename = append_string(filename, n_str);
    free(n_str);
    return (filename);
}

static char *get_tmp_filename_prefix(int pid)
{
    char *prefix;
    char *n_str;

    prefix = ft_strdup(MINISHELL_TMP_PREFIX);
    n_str = ft_itoa(pid);
    prefix = append_string(prefix, n_str);
    free(n_str);
    prefix = append_char(prefix, '-');
    return (prefix);
}

t_minishell *minishell_init(char **envp)
{
    t_minishell *ctx;

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
    ctx->tmpfilename_prefix = get_tmp_filename_prefix(ctx->pid);
    return (ctx);
}

t_result minishell_destroy(t_minishell *ctx)
{
    if (ctx == NULL)
        return (OP_INVALID);
    if (ctx->vars != NULL)
        hmap_destroy(ctx->vars);
    free(ctx->tmpfilename_prefix);
    free(ctx);
    return (OP_OK);
}

