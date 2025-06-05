/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:47:36 by user1             #+#    #+#             */
/*   Updated: 2025/06/05 16:51:58 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int parser1_10(t_parser_i *pi)
{
    if (ft_isspace(*pi->cchar))
        return (10);
    if (*pi->cchar == '\'')
    {
        pi->cw = ft_strdup("");
        return (11);
    }
    if (*pi->cchar == '"')
    {
        pi->cw = ft_strdup("");
        return (12);
    }
    if (*pi->cchar == '\0')
        return (0);
    append_cw_char(pi, *pi->cchar);
    return (13);
}

int parser1_11(t_parser_i *pi)
{
    if (*pi->cchar == '\'')
        return (13);
    if (*pi->cchar == '\0')
    {
        ft_dprintf(2, "Closing apostrophe missing 1_11\n");
        return (-1);
    }
    append_cw_char(pi, *pi->cchar);
    return (11);
}

int parser1_12(t_parser_i *pi)
{
    if (*pi->cchar == '"')
        return (13);
    if (*pi->cchar == '\0')
    {
        ft_dprintf(2, "Closing quotation mark missing 1_12\n");
        return (-1);
    }
    append_cw_char(pi, *pi->cchar);
    return (12);
}

int parser1_13(t_parser_i *pi)
{
    if (*pi->cchar == '\0')
    {
        append_word(pi);
        return (0);
    }
    if (ft_isspace(*pi->cchar))
    {
        append_word(pi);
        return (1);
    }
    if (*pi->cchar == '\'')
        return (11);
    if (*pi->cchar == '"')
        return (12);
    append_cw_char(pi, *pi->cchar);
    return (13);
}
