/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:27:13 by user1             #+#    #+#             */
/*   Updated: 2025/06/10 22:08:28 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
        ft_dprintf(2, "Missing closing double quote\n");
        pi->state = -1;
    }
    else
        append_cw_char(pi, *pi->cchar);
    return (OP_OK);
}

t_list  *split_simple_commands(t_list *words)
{
    t_list  *simple_cmds;

    if (words == NULL)
        return (NULL);
    simple_cmds = NULL;
    if (ft_strcmp(words->content, "|") == 0
        || ft_strcmp(ft_lstlast(words)->content, "|"))
    {
        ft_dprintf(2, "minishell: : syntax error near unexpected token `|'");
        // TODO
        return (NULL);
    }
    return (simple_cmds);
}
