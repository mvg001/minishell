/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:49:36 by user1             #+#    #+#             */
/*   Updated: 2025/06/19 14:34:51 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

void parser_print_ps(t_ps *ps)
{
    char    *aux;

    if (ps == NULL)
    {
        ft_dprintf(2, "parser_print_ps: NULL ps\n");
        return ;
    }
    ft_dprintf(2, "parser_print_ps:\n");
    ft_dprintf(2, "\tstate: [%d]\n", ps->state);
    ft_dprintf(2, "\tremainding text: [%s]\n", ps->cchar);
    aux = ft_strdup(ps->cw);
    substitute_dc1_dc2_quotes(aux);
    ft_dprintf(2, "\tcurrent word: [%s]\n", aux);
    free(aux);
    ft_dprintf(2, "\tkey: [%s]\n", ps->key);
    if (ps->words != NULL)
        parser_print_words("parser_print_ps", ps->words);
    ft_putchar_fd('\n', 2);
}

/*
    '\'' => DC1 (0x11)
    '""  => DC2 (0x12)
*/
void    substitute_quotes_dc1_dc2(char *str)
{
    if (str == NULL)
        return ;
    while (*str)
    {
        if (*str == '\'')
            *str = DC1;
        else if (*str == '"')
            *str = DC2;
        str++;
    }
}

void    substitute_dc1_dc2_quotes(char *str)
{
    if (str == NULL)
        return ;
    while (*str)
    {
        if (*str == DC1)
            *str = '\'';
        else if (*str == DC2)
            *str = '"';
        str++;
    }
}

void    *cleanup_quotes_dc1_dc2(void *ptr)
{
    char    *src;
    char    *dst;

    if (ptr == NULL)
        return (ft_strdup(""));
    src = (char *)ptr - 1;
    dst = NULL;
    while (*++src)
    {
        if (*src == '\'' || *src == '"')
            continue;
        if (*src == DC1)
            dst = append_char(dst, '\'');
        else if (*src == DC2)
            dst = append_char(dst, '"');
        else
            dst = append_char(dst, *src);
    }
    return (dst);
}
