/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:47:36 by user1             #+#    #+#             */
/*   Updated: 2025/06/03 11:46:06 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "libft.h"

static char *append_char(char *w, char c)
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

static char *append_string(char *w, char *str)
{
    char *output;

    if (w == NULL)
    {
        if (str == NULL)
        {
            return (NULL);
        }
        return (ft_strdup(str));
    }
    if (str == NULL)
        return (w);
    output = ft_strjoin(w, str);
    free(w);
    return (output);
}

static int is_first_char_identifier(char c)
{
    return (c == '_' || ft_isalpha(c));
}

t_list  *minishell_parse_line(t_minishell *ctx, char *line)
{
    t_list  *words;
    char *b;

    if (ctx == NULL || line == NULL)
        return (NULL);
    b = NULL;
    words = NULL;
    while (*line)
    {
        if (ft_strchr(IFS, *line) == NULL)
        {
            line++;
            continue;
        }
        if (*line == '|')
            ft_lstadd_back(&words, ft_lstnew(ft_strdup("|")));
        else if (*line == '<')
        {
            
        }
        line++;
    }
    return (words);
}

t_pipeline *minishell_parse_words(t_minishell *ctx, t_list *words)
{
    t_pipeline  *pipeline;

    if (ctx == NULL || words == NULL)
        return (NULL);
    pipeline = NULL; // TODO
    return (pipeline);
}