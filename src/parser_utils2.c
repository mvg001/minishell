/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:49:36 by user1             #+#    #+#             */
/*   Updated: 2025/06/14 12:13:25 by user1            ###   ########.fr       */
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