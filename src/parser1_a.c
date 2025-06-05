/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:28:02 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/05 11:19:40 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int parser1_1a(t_parser_i *pi)
{
    if (*pi->cchar == '$')
    {
        pi->key = NULL;
        return (4);
    }
    if (*pi->cchar == '\'')
        return 6;
    if (*pi->cchar == '"')
        return 7;
    if (*pi->cchar == '\0')
    {
        append_word(pi);
        return (0);
    }
    append_cw_char(pi, *pi->cchar);
    return (1);
}

int parser1_1(t_parser_i *pi)
{
    if (ft_isspace(*pi->cchar))
    {
        append_word(pi);
        return (1);
    }
    if (*pi->cchar == '|')
    {
        append_word(pi);
        pi->cw = ft_strdup("|");
        append_word(pi);
        return (1);
    }
    if (*pi->cchar == '<' || *pi->cchar == '>')
    {
        append_word(pi);
        append_cw_char(pi, *pi->cchar);
        if (*pi->cchar == '<')
            return (2);
        else
            return (3);
    }
    return (parser1_1a(pi));
}

int parser1_2(t_parser_i *pi)
{
    if (*pi->cchar == '<')
    {
        append_cw_char(pi, '<');
        append_word(pi);
        return (10);
    }
    append_word(pi);
    if (*pi->cchar == '\0')
        return (0);
    pi->cchar--;
    return (1);
}

int parser1_3(t_parser_i *pi)
{
    if (*pi->cchar == '>')
    {
        append_cw_char(pi, '>');
        append_word(pi);
        return (1);
    }
    append_word(pi);
    if (*pi->cchar == '\0')
        return (0);
    pi->cchar--;
    return (1);
}

int parser1_4(t_parser_i *pi)
{
    if (is_first_char_identifier(*pi->cchar))
    {
        pi->key = append_char(pi->key, *pi->cchar);
        return (5);
    }
    pi->cw = append_char(pi->cw, '$');
    pi->cchar--;
    return (1);
}
