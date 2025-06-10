/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:24:11 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/10 14:38:19 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include "libft.h"
#include "parser.h"

static t_result tokenizer_1a(t_parser_i *pi)
{
    if (*pi->cchar == '"')
    {
        append_cw_char(pi, '"');
        pi->state = 5;
    }
    else if (*pi->cchar == '\0' || *pi->cchar == '#')
    {
        append_word(pi);
        pi->state = 0;
    }
    else append_cw_char(pi, *pi->cchar);
    return (OP_OK);
}

t_result tokenizer_1(t_parser_i *pi)
{
    if (pi == NULL)
        return (OP_INVALID);
    if (ft_isspace(*pi->cchar))
        append_word(pi);
    else if (*pi->cchar == '|')
    {
        append_word(pi);
        append_cw_char(pi, '|');
        append_word(pi);
    }
    else if (*pi->cchar == '<')
        pi->state = 2;
    else if (*pi->cchar == '>')
        pi->state = 3;
    else if (*pi->cchar == '\'')
    {
        append_cw_char(pi, '\'');
        pi->state = 4;
    }
    else  return (tokenizer_1a(pi));
    return (OP_OK);
}

t_result tokenizer_2(t_parser_i *pi)
{
    append_word(pi);
    pi->state = 1;
    if (*pi->cchar == '<')
    {
        append_cw_string(pi, "<<");
        append_word(pi);
    }
    else
    {
        append_cw_char(pi, '<');
        append_word(pi);
        pi->cchar--;
    }
    return (OP_OK);
}

t_result tokenizer_3(t_parser_i *pi)
{
    append_word(pi);
    pi->state = 1;
    if (*pi->cchar == '>')
    {
        append_cw_string(pi, ">>");
        append_word(pi);
    }
    else
    {
        append_cw_char(pi, '>');
        append_word(pi);
        pi->cchar--;
    }
    return (OP_OK);
}

t_result tokenizer_4(t_parser_i *pi)
{
    if (*pi->cchar == '\'')
    {
        append_cw_char(pi, '\'');
        pi->state = 1;
    }
    else if (*pi->cchar == '\0')
    {
        ft_dprintf(2, "Missing closing apostrophe\n");
        pi->state = -1;
    }
    else
        append_cw_char(pi, *pi->cchar);
    return (OP_OK);
}
