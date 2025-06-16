/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_command1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:37:40 by user1             #+#    #+#             */
/*   Updated: 2025/06/16 18:26:11 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include "libft.h"
#include "minishell.h"

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

    if (simple_command == NULL)
        return ;
    sc = *simple_command;
    if (sc->args != NULL)
        ft_dispose_split(sc->args);
    if (sc->envp != NULL)
        ft_dispose_split(sc->envp);
    if (sc->input_file != NULL)
        free(sc->input_file);
    if (sc->output_file != NULL)
        free(sc->output_file);
    *simple_command = NULL;
}

void    msh_print_command(int fd, t_command *sc)
{
    if (fd <= 0 || sc == NULL)
        return ;
    ft_dprintf(fd, "{\n\tinput_file='%s'\n", sc->input_file);
    ft_dprintf(fd, "{\n\tis_here_doc='%s'\n", sc->is_here_doc);
    ft_dprintf(fd, "\toutput_file='%s'\n", sc->output_file);
    ft_dprintf(fd, "\tappend_output=%d\n", sc->append_output);
    ft_dprintf(fd, "\targs: [\n");
    while (*sc->args)
        ft_dprintf(fd, "\t\t'%s'\n", *sc->args++);
    ft_dprintf(fd, "\t]\n}\n");
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
