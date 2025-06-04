/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:28:02 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/04 19:24:32 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int parser1_1a(t_list **words, char **cw, char **key, char c)
{
    if (c == '$')
        return (*key = NULL, 4);
    if (c == '\'')
        return 6;
    if (c == '"')
        return 7;
    if (c == '\0')
    {
        append_word(words, cw);
        return (0);
    }
    *cw = append_char(*cw, c);
    return (1);
}

int parser1_1(t_list **words, char **cw, char **key, char c)
{
    if (ft_isspace(c))
    {
        append_word(words, cw);
        return (1);
    }
    if (c == '|')
    {
        append_word(words, cw);
        *cw = ft_strdup("|");
        append_word(words, cw);
        return (1);
    }
    if (c == '<' || c == '>')
    {
        append_word(words, cw);
        *cw = append_char(*cw, c);
        if (c == '<')
            return (2);
        else
            return (3);
    }
    return (parser1_1a(words, cw, key, c));
}

int parser1_2(t_list **words, char **cw, char **c)
{
    if (**c == '<')
    {
        *cw = append_char(*cw, '<');
        append_word(words, cw);
        return (10);
    }
    append_word(words, cw);
    if (**c == '\0')
        return (0);
    (*c)--;
    return (1);
}

int parser1_3(t_list **words, char **cw, char **c)
{
    if (**c == '>')
    {
        *cw = append_char(*cw, '>');
        append_word(words, cw);
        return (1);
    }
    append_word(words, cw);
    if (**c == '\0')
        return (0);
    (*c)--;
    return (1);
}

int parser1_4(char **cw, char **key, char **c)
{
    if (is_first_char_identifier(**c))
    {
        *key = append_char(*key, **c);
        return (5);
    }
    *cw = append_char(*cw, '$');
    (*c)--;
    return (1);
}
