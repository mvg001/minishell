/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:19:54 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/11 16:15:56 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include "libft.h"
#include "parser.h"

t_result pi_append_cw_char(t_ps *pi, char c)
{
    char    s[2];
    char    *output;

    s[0] = c;
    s[1] = '\0';
    if (pi->cw == NULL)
    {
        pi->cw = ft_strdup(s);
        if (pi->cw == NULL)
            return (OP_FAILED);
        return (OP_OK);
    }
    output = ft_strjoin(pi->cw, s);
    if (output == NULL)
        return (OP_FAILED);
    free(pi->cw);
    pi->cw = output;
    return (OP_OK);
}

t_result pi_append_cw_string(t_ps *pi, char *str)
{
    char *output;

    if (pi->cw == NULL)
    {
        if (str == NULL)
            return (OP_OK);
        pi->cw = ft_strdup(str);
        if (pi->cw == NULL)
            return (OP_FAILED);
        return (OP_OK);
    }
    if (str == NULL)
        return (OP_OK);
    output = ft_strjoin(pi->cw, str);
    if (output == NULL)
        return (OP_FAILED);
    free(pi->cw);
    pi->cw = output;
    return (OP_OK);
}

t_result pi_append_word(t_ps *pi)
{
    t_list *new_node;

    if (pi == NULL || pi->cw == NULL)
        return (OP_OK);
    new_node = ft_lstnew(pi->cw);
    if (new_node == NULL)
        return (OP_FAILED);
    ft_lstadd_back(&pi->words, new_node);
    pi->cw = NULL;
    return (OP_OK);
}

char *append_char(char *w, char c)
{
    char    s[2];
    char    *output;

    s[0] = c;
    s[1] = '\0';
    if (w == NULL)
        return ft_strdup(s);
    output = ft_strjoin(w, s);
    free(w);
    return (output);
}
