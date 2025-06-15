/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:19:54 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/15 13:09:16 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include "libft.h"
#include "parser.h"

t_result ps_append_cw_char(t_ps *ps, char c)
{
    char    s[2];
    char    *output;

    s[0] = c;
    s[1] = '\0';
    if (ps->cw == NULL)
    {
        ps->cw = ft_strdup(s);
        if (ps->cw == NULL)
            return (OP_FAILED);
        return (OP_OK);
    }
    output = ft_strjoin(ps->cw, s);
    if (output == NULL)
        return (OP_FAILED);
    free(ps->cw);
    ps->cw = output;
    return (OP_OK);
}

t_result ps_append_cw_string(t_ps *ps, char *str)
{
    char *output;

    if (ps->cw == NULL)
    {
        if (str == NULL)
            return (OP_OK);
        ps->cw = ft_strdup(str);
        if (ps->cw == NULL)
            return (OP_FAILED);
        return (OP_OK);
    }
    if (str == NULL)
        return (OP_OK);
    output = ft_strjoin(ps->cw, str);
    if (output == NULL)
        return (OP_FAILED);
    free(ps->cw);
    ps->cw = output;
    return (OP_OK);
}

t_result ps_append_word(t_ps *ps)
{
    t_list *new_node;

    if (ps == NULL || ps->cw == NULL)
        return (OP_OK);
    new_node = ft_lstnew(ps->cw);
    if (new_node == NULL)
        return (OP_FAILED);
    ft_lstadd_back(&ps->words, new_node);
    ps->cw = NULL;
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

void    parser_print_words(char *title, t_list *words)
{
    char *aux;

    ft_dprintf(2, "%s\n", title);
    while (words != NULL)
    {
        aux = ft_strdup(words->content);
        substitute_dc1_dc2_quotes(aux);
        ft_dprintf(2, "[%s]\n", aux);
        free(aux);
        words = words->next;
    }
}