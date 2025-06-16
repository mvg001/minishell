/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_command2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:20:54 by user1             #+#    #+#             */
/*   Updated: 2025/06/16 18:33:05 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include "libft.h"
#include "minishell.h"

t_result    msh_command_set_args(t_command *sc, char **args)
{
    if (sc == NULL)
        return (OP_INVALID);
    if (sc->args != NULL)
        ft_dispose_split(sc->args);
    sc->args = args;
    return (OP_OK);
}

