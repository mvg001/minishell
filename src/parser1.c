/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:47:36 by user1             #+#    #+#             */
/*   Updated: 2025/06/05 12:07:09 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "libft.h"

t_list  *minishell_parse_line(t_minishell *ctx, char *line)
{
    int         state;
    t_parser_i  pi;

    if (ctx == NULL || line == NULL)
        return (NULL);
    pi.cw = NULL;
    pi.words = NULL;
    pi.cchar = line;
    pi.key = NULL;
    state = 1;
    while (state > 0)
    {
        if (state == 1)
            state = parser1_1(&pi);
        else if (state == 2)
            state = parser1_2(&pi);
        else if (state == 3)
            state = parser1_3(&pi);
        else if (state == 4)
            state = parser1_4(&pi);
        else if (state == 5)
            state = parser1_5(&pi, ctx->vars);
        else if (state == 6)
            state = parser1_6(&pi);
        else if (state == 7)
            state = parser1_7(&pi);
        else if (state == 8)
            state = parser1_8(&pi);
        else if (state == 9)
            state = parser1_9(&pi, ctx->vars);
        else if (state == 10)
            state = parser1_10(&pi);
        else if (state == 11)
            state = parser1_11(&pi);
        else if (state == 12)
            state = parser1_12(&pi);
        else if (state == 13)
            state = parser1_13(&pi);
        else
        {
            ft_dprintf(2, "*** INVALID STATE %d\n", state);
            break;
        }
        pi.cchar++;
    }
    if (pi.key != NULL)
        free(pi.key);
    pi.key = NULL;
    if (pi.cw != NULL)
        free(pi.cw);
    pi.cw = NULL;
    if (state < 0)
    {
        ft_lstclear(&pi.words, free);
        ft_dprintf(2, "* Invalid input\n");
        return (NULL);
    }
    return (pi.words);
}
