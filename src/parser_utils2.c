/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:49:36 by user1             #+#    #+#             */
/*   Updated: 2025/06/14 18:34:16 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

void parser_print_ps(t_ps *ps)
{
    if (ps == NULL)
    {
        ft_dprintf(2, "parser_print_ps: NULL ps\n");
        return ;
    }
    ft_dprintf(2, "parser_print_ps:\n");
    ft_dprintf(2, "\tstate: [%d]\n", ps->state);
    ft_dprintf(2, "\tremainding text: [%s]\n", ps->cchar);
    ft_dprintf(2, "\tcurrent word: [%s]\n", ps->cw);
    ft_dprintf(2, "\tkey: [%s]\n", ps->key);
    if (ps->words != NULL)
        parser_print_words("parser_print_ps", ps->words);
    ft_putchar_fd('\n', 2);
}

/*
    '\'' => DC1 (0x11)
    '""  => DC2 (0x12)
*/
void    substitute_quotes_dc1_dc2(unsigned int pos, char *ptrc)
{
    (void)pos;
    if (*ptrc == '\'')
        *ptrc = '\x11';
    else if (*ptrc == '"')
        *ptrc = '\x12';
}

void    *cleanup_quotes_dc1_dc2(void *ptr)
{
    char    *src;
    char    *dst;

    if (ptr == NULL)
        return (ft_strdup(""));
    src = (char *)ptr - 1;
    dst = ft_strdup("");
    while (*++src)
    {
        if (*src == '\'' || *src == '"')
            continue;
        if (*src == '\x11')
            dst = append_char(dst, '\'');
        else if (*src == '\x12')
            dst = append_char(dst, '"');
        else
            dst = append_char(dst, *src);
    }
    return (dst);
}
