/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:19:54 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/05 15:54:03 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void append_cw_char(t_parser_i *pi, char c)
{
    char    s[2];
    char    *output;

    s[0] = c;
    s[1] = '\0';
    if (pi->cw == NULL)
    {
        pi->cw = ft_strdup(s);
        return ;
    }
    output = ft_strjoin(pi->cw, s);
    free(pi->cw);
    pi->cw = output;
}

void append_cw_string(t_parser_i *pi, char *str)
{
    char *output;

    if (pi->cw == NULL)
    {
        if (str == NULL)
            return ;
        pi->cw = ft_strdup(str);
        return ;
    }
    if (str == NULL)
        return ;
    output = ft_strjoin(pi->cw, str);
    free(pi->cw);
    pi->cw = output;
}

int is_first_char_identifier(char c)
{
    return (c == '_' || ft_isalpha(c));
}

void append_word(t_parser_i *pi)
{
    if (pi == NULL || pi->cw == NULL)
        return ;
    ft_lstadd_back(&pi->words, ft_lstnew(pi->cw));
    pi->cw = NULL;
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
