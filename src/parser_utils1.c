/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:19:54 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/04 18:23:25 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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

char *append_string(char *w, char *str)
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

int is_first_char_identifier(char c)
{
    return (c == '_' || ft_isalpha(c));
}

void append_word(t_list **words, char **w)
{
    if (words == NULL || w == NULL || *w == NULL)
        return ;
    ft_lstadd_back(words, ft_lstnew(*w));
    *w = NULL;
}

