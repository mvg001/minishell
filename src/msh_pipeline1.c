/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pipeline1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:37:29 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/21 20:32:49 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stddef.h>
#include <unistd.h>

t_pipeline	*msh_create_pipeline(void)
{
	t_pipeline	*pline;

	pline = ft_calloc(1, sizeof(t_pipeline));
    if (pline == NULL)
		return (NULL);
	return (pline);
}

void	msh_destroy_pipeline(t_pipeline *pline)
{
    int         i;

    if (pline == NULL)
        return ;
    if (pline->n_commands > 0)
    {
        i = -1;
        while (++i < pline->n_commands)
            msh_destroy_command(&pline->commands[i]);
        free(pline->commands);
    }
    if (pline->envp != NULL)
        ft_dispose_split(pline->envp);
    free(pline);
}

void	msh_print_pipeline(int fd, t_pipeline *pline)
{
    int i;

    if (pline == NULL || fd <= 0)
        return ;
    ft_dprintf(fd, "t_pipeline{\n\tn_commands=%d\n", pline->n_commands);
    ft_dprintf(2, "\tcommands:\n");
    if (pline->commands == NULL)
        ft_dprintf(fd, "\t\tNULL");
    else
    {
        i = -1;
        while (++i < pline->n_commands)
            msh_print_command(fd, pline->commands[i]);
    }
    if (pline->envp == NULL)
        ft_dprintf(fd, "envp: NULL\n");
    else
        ft_print_argv(2, "envp", pline->envp);
    ft_dprintf(fd, "}\n");
}
