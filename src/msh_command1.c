/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_command1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:37:40 by user1             #+#    #+#             */
/*   Updated: 2025/06/21 20:32:18 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include "libft.h"
#include "minishell.h"
#include <stddef.h>

t_command   *msh_create_command(void)
{
    t_command   *scmd;

    scmd = ft_calloc(1, sizeof(t_command));
    if (scmd == NULL)
        return (NULL);
    return (scmd);
}

void    msh_destroy_command(t_command **simple_command)
{
    t_command *sc;
    size_t  len;

    if (simple_command == NULL)
        return ;
    len = ft_strlen(MINISHELL_TMP_PREFIX);
    sc = *simple_command;
    if (sc->args != NULL)
        ft_dispose_split(sc->args);
    if (sc->input_file != NULL)
    {
        if (sc->is_here_doc)
        {
            if (ft_strncmp(sc->input_file, MINISHELL_TMP_PREFIX, len) == 0)
                if (access(sc->input_file, F_OK) == 0)
                    unlink(sc->input_file);
        }
        free(sc->input_file);
    }
    if (sc->output_file != NULL)
        free(sc->output_file);
    *simple_command = NULL;
}

void    msh_print_command(int fd, t_command *sc)
{
    if (fd <= 0 || sc == NULL)
        return ;
    ft_dprintf(fd, "t_command{\n\tinput_file='%s'\n", sc->input_file);
    ft_dprintf(fd, "\n\tis_here_doc='%d'\n", sc->is_here_doc);
    ft_dprintf(fd, "\toutput_file='%s'\n", sc->output_file);
    ft_dprintf(fd, "\tappend_output=%d\n", sc->append_output);
    ft_print_argv(fd, "args:", sc->args);
    ft_dprintf(fd, "\n}\n");
}

t_result    msh_command_set_input(t_command *sc, char *filename, int is_here_doc)
{
    if (sc == NULL)
        return (OP_INVALID);
    if (filename != NULL)
    {
        sc->input_file = ft_strdup(filename);
        sc->is_here_doc = is_here_doc != 0;
        if (sc->input_file == NULL)
            return (OP_FAILED);
    }
    else
    {
        sc->input_file = NULL;
        sc->is_here_doc = 0;
    }
    return (OP_OK);
}

t_result    msh_command_set_output(t_command *sc, char *filename, int is_app_mode)
{
    if (sc == NULL)
        return (OP_INVALID);
    if (filename != NULL)
    {
        sc->output_file = ft_strdup(filename);
        sc->append_output = is_app_mode != 0;
        if (sc->output_file == NULL)
            return (OP_FAILED);
    }
    else
    {
        sc->output_file = NULL;
        sc->append_output = 0;
    }
    return (OP_OK);
}
