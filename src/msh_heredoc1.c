/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_heredoc1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:32:16 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/21 19:41:14 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <readline/readline.h>
#include "hmap.h"
#include "libft.h"
#include "minishell.h"

t_result    get_heredoc(char *delim, char *output_filename)
{
    int fd;
    char *line;

    if (delim == NULL || output_filename == NULL)
        return (OP_INVALID);
    fd = open(output_filename, O_CREAT|O_WRONLY, 0x600);
    if (fd < 0)
        return (OP_FAILED);
    while (1)
    {
        line = readline("> ");
        if (line == NULL)
        {
            ft_dprintf(2, 
                "minishell: warning: here-document delimited by end-of-file"
                    " (wanted `%s')", delim);
            break;
        }
        if (ft_strcmp(line, delim) == 0)
            break;
        ft_dprintf(fd, "%s\n", line);
        free(line);
    }
    close(fd);
    return (OP_OK);
}

t_result    msh_process_pipeline_heredocs(t_minishell *ctx, t_pipeline *ppl)
{
    int i;
    char *filename;
    char *delim;

    if (ppl == NULL)
        return (OP_INVALID);
    i = -1;
    while (++i < ppl->n_commands)
    {
        if (ppl->commands[i]->is_here_doc)
            continue;
        filename = get_tmp_filename(ctx);
        delim = ppl->commands[i]->input_file;
        ppl->commands[i]->input_file = filename;
        get_heredoc(delim, filename);
        free(delim);
    }
    return (OP_OK);
}
