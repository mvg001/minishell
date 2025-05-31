/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:42:47 by mvassall          #+#    #+#             */
/*   Updated: 2025/05/29 17:37:55 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>
#include "libft.h"
#include "hmap.h"
#include "minishell.h"


static int interactive(t_minishell *ctx)
{
    char *line;

    using_history();
    while (1)
    {
        line = readline("minishell$ ");
        if (line == NULL || ft_strcmp(line, "exit"))
            break;
        ctx->last_status = proc_line(ctx, line);
        add_history(line);
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
    while (1)
    {
        aux = gnl_getline(0, rb);
        if (aux == NULL || ft_strcmp(aux, "exit\n") == 0)
            break;
        line = ft_strtrim(aux, "\n");
        free(aux);
        ctx->last_status = proc_line(ctx, line);
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
    if (isatty(0))
        status = interactive(ctx);
    else
        status = non_interactive(ctx);
    minishell_destroy(ctx);
    return (status);
}




/*
int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    (void)envp;
    char *line;
    char *val;
    int i;
    t_buf *buf = gnl_alloc_buf(4096);

    t_hmap *hm = hmap_create(128, hash_func);
    if (hm == NULL)
    {
        ft_dprintf(2, "hmap_create failed\n");
        return (1);
    }
    i = 0;
    while (envp[i] != NULL)
    {
        char **fields = ft_split(envp[i], '=');
        if (fields != NULL)
        {
            hmap_put(hm, fields[0], fields[1]);
            ft_dispose_split(fields);
        }
        i++;
    }
    hmap_dump(2, hm);
    line = NULL;
    while (1)
    {
        ft_dprintf(1, "minishell$ ");
        val = gnl_getline(0, buf);
        line = ft_strtrim(val, "\n");
        free(val);
        if (line == NULL || ft_strcmp(line, "exit") == 0)
            break;
        char **fields = ft_split(line, ' ');
        free(line);
        if (fields != NULL)
        {
            int count = ft_split_count(fields);
            if (count == 2 && ft_strcmp(fields[0], "show") == 0)
            {
                char *val = hmap_lookup(hm, fields[1]);
                ft_dprintf(1, "'%s' => '%s'\n", fields[1], val);
                free(val);
            } else if (count == 3 && ft_strcmp(fields[0], "put") == 0)
            {
                int result = hmap_put(hm, fields[1], fields[2]);
                ft_dprintf(1, "%s\n", result == OP_OK ? "OK" : "FAILED");
            } else if (count == 2 && ft_strcmp(fields[0], "del") == 0)
            {
                int result = hmap_delete(hm, fields[1]);
                ft_dprintf(1, "%s\n", result == OP_OK ? "OK" : "FAILED");
            } else if (count == 1 && ft_strcmp(fields[0], "dump") == 0)
            {
                hmap_dump(1, hm);
            } else
            {
                ft_dprintf(2, "invalid input\n");
            }
            ft_dispose_split(fields);
        }
    }
    free(line);
    gnl_dispose(buf);
    hmap_destroy(hm);
	return 0;
}
*/


