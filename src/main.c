/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:42:47 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/20 07:16:47 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "libft.h"
#include "hmap.h"
#include "minishell.h"

static int process_line(t_minishell *ctx, char *line)
{
    char  **tokens;
    t_pipeline  *cmds;

    if (ctx == NULL || line == NULL)
    {
        return (-1);
    }
    tokens = minishell_parse_line(ctx, line);
    cmds = minishell_parse_words(ctx, tokens);
    ft_dispose_split(tokens);
    ctx->last_status = minishell_execute(ctx, cmds);
    // pipeline_destroy(cmds);
    return (0);
}

static int interactive(t_minishell *ctx)
{
    char *line;

    ctx->is_interactive = 1;
    using_history();
    while (1)
    {
        line = readline("minishell$ ");
        if (line == NULL || ft_strcmp(line, "exit") == 0)
            break;
        add_history(line);
        process_line(ctx, line);
        free(line);
        line = NULL;
    }
    free(line);
    return (EXIT_SUCCESS);
}

static int non_interactive(t_minishell *ctx)
{
    char    *line;
    char    *aux;
    t_buf   *rb;

    rb = gnl_alloc_buf(4096);
    if (rb == NULL)
        return (OP_FAILED);
    ctx->is_interactive = 0;
    while (1)
    {
        aux = gnl_getline(0, rb);
        if (aux == NULL || ft_strcmp(aux, "exit\n") == 0)
            break;
        line = ft_strtrim(aux, "\n");
        free(aux);
        process_line(ctx, line);
        free(line);
        line = NULL;
    }
    free(line);
    gnl_dispose(rb);
    return (EXIT_SUCCESS);
}

int main(int ac, char **av, char **envp)
{
    t_minishell *ctx;
    int         status;

    (void)ac;
    (void)av;
    ctx = minishell_init(envp);
    if (ctx == NULL)
    {
        ft_dprintf(2, "unable to load environment vars\n");
        exit(EXIT_FAILURE);
    }
    hmap_dump(2, ctx->vars);
    ctx->pid = ft_getpid();
    if (isatty(0))
        status = interactive(ctx);
    else
        status = non_interactive(ctx);
    minishell_destroy(ctx);
    return (status);
}
