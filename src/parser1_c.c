/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:47:36 by user1             #+#    #+#             */
/*   Updated: 2025/06/05 12:07:26 by user1            ###   ########.fr       */
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
    {
        append_word(pi);
        return (1);
    }
    if (*pi->cchar == '\0')
    {
        ft_dprintf(2, "Closing apostrophe missing\n");
        return (-1);
    }
    append_cw_char(pi, *pi->cchar);
    return (11);
}

int parser1_12(t_parser_i *pi)
{
    if (*pi->cchar == '"')
    {
        append_word(pi);
        return (1);
    }
    if (*pi->cchar == '\0')
    {
        ft_dprintf(2, "Closing quotation mark missing\n");
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
    append_cw_char(pi, *pi->cchar);
    return (13);
}