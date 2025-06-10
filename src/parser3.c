/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:27:13 by user1             #+#    #+#             */
/*   Updated: 2025/06/10 14:27:50 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_result tokenizer_5(t_parser_i *pi)
{
    if (*pi->cchar == '"')
    {
        append_cw_char(pi, '"');
        pi->state = 1;
    }
    else if (*pi->cchar == '\0')
    {
        ft_dprintf(2, "Missing closing quotation mark\n");
        pi->state = -1;
    }
    else
        append_cw_char(pi, *pi->cchar);
    return (OP_OK);
}
