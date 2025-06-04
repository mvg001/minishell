/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:47:36 by user1             #+#    #+#             */
/*   Updated: 2025/06/04 18:12:44 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "hmap.h"
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

static void append_word(t_list **words, char **w)
{
    if (words == NULL || w == NULL || *w == NULL)
        return ;
    ft_lstadd_back(words, ft_lstnew(*w));
    *w = NULL;
}

t_list  *minishell_parse_line(t_minishell *ctx, char *line)
{
    t_list  *words;
    char    *cw;
    char    *key;
    int     state;
    int     error_flag;

    if (ctx == NULL || line == NULL)
    {
        return (NULL);
    }
    cw = NULL;
    words = NULL;
    error_flag = 0;
    key = NULL;
    state = 1;
    while (state != 0)
    {
        if (state == 1)
        {
            if (ft_isspace(*line))
            {
                append_word(&words, &cw);
                cw = NULL;
            }
            else if (*line == '|')
            {
                append_word(&words, &cw);
                cw = ft_strdup("|");
                append_word(&words, &cw);
            }
            else if (*line == '<')
            {
                append_word(&words, &cw);
                cw = append_char(cw, *line);
                state = 2;
            }
            else if (*line == '>')
            {
                append_word(&words, &cw);
                cw = append_char(cw, *line);
                state = 3;
            }
            else if (*line == '$')
            {
                key = NULL;
                state = 4;
            }
            else if (*line == '\'')
                state = 6;
            else if (*line == '"')
                state = 7;
            else if (*line == '\0')
            {
                state = 0;
                append_word(&words, &cw);
            }
            else
                cw = append_char(cw, *line);
        }
        else if (state == 2)
        {
            if (*line == '<')
            {
                cw = append_char(cw, *line);
                append_word(&words, &cw);
                state = 10;
            }
            else
            {
                state = 1;
                append_word(&words, &cw);
                if (*line == '\0')
                    state = 0;
                else
                    line--;
            }
        }
        else if (state == 3)
        {
            state = 1;
            if (*line == '>')
            {
                cw = append_char(cw, *line);
                append_word(&words, &cw);
            }
            else
            {
                append_word(&words, &cw);
                if (*line == '\0')
                    state = 0;
                else
                    line--;
            }
        }
        else if (state == 4)
        {
            if (is_first_char_identifier(*line))
            {
                key = append_char(key, *line);
                state = 5;
            }
            else
            {
                line--;
                cw = append_char(cw, '$');
                state = 1;
            }
        }
        else if (state == 5)
        {
            if (*line == '_' || ft_isalnum(*line))
                key = append_char(key, *line);
            else
            {
                line--;
                cw = append_string(cw, hmap_lookup(ctx->vars, key));
                free(key);
                key = NULL;
                state = 1;
            }              
        }
        else if (state == 6)
        {
            if (*line == '\0')
            {
                error_flag = 1;
                ft_dprintf(2, "Closing apostrophe missing\n");
                state = 0;
            }
            else if (*line == '\'')
                state = 1;
            else
                cw = append_char(cw, *line);
        }
        else if (state == 7)
        {
            if (*line == '\0')
            {
                error_flag = 1;
                ft_dprintf(2, "Closing quotation mark missing\n");
                state = 0;
            }
            else if (*line == '$')
            {
                key = NULL;
                state = 8;
            }
            else if (*line == '"')
                state = 1;
            else
                cw = append_char(cw, *line);
        }
        else if (state == 8)
        {
            if (*line == '\0')
            {
                error_flag = 1;
                ft_dprintf(2, "Closing quotation mark missing\n");
                state = 0;
            }
            else if (is_first_char_identifier(*line))
            {
                key = append_char(key, *line);
                state = 9;
            }
            else
            {
                line--;
                cw = append_char(cw, '$');
            }
        }
        else if (state == 9)
        {
            if (*line == '\0')
            {
                error_flag = 1;
                ft_dprintf(2, "Closing quotation mark missing\n");
                state = 0;
            }
            else if (*line == '_' || ft_isalnum(*line))
                key = append_char(key, *line);
            else
            {
                line--;
                cw = append_string(cw, hmap_lookup(ctx->vars, key));
                free(key);
                key = NULL;
                state = 7;
            }
        }
        else if (state == 10)
        {
            if (ft_isspace(*line))
                state = 10;
            else if (*line == '\'')
            {
                cw = ft_strdup("");
                state = 11;
            }
            else if (*line == '"')
            {
                cw = ft_strdup("");
                state = 12;
            }
            else if (*line == '\0')
                state = 0;
            else
            {
                cw = append_char(cw, *line);
                state = 13;
            }
        }
        else if (state == 11)
        {
            if (*line == '\'')
            {
                append_word(&words, &cw);
                state = 1;
            }
            else if (*line == '\0')
            {
                error_flag = 1;
                ft_dprintf(2, "Closing apostrophe missing\n");
                state = 0;
            }
            else
                cw = append_char(cw, *line);
        }
        else if (state == 12)
        {
            if (*line == '"')
            {
                append_word(&words, &cw);
                state = 1;
            }
            else if (*line == '\0')
            {
                error_flag = 1;
                ft_dprintf(2, "Closing quotation mark missing\n");
                state = 0;
            }
            else
                cw = append_char(cw, *line);
        }
        else if (state == 13)
        {
            if (*line == '\0')
            {
                append_word(&words, &cw);
                state = 0;
            }
            else if (ft_isspace(*line))
            {
                append_word(&words, &cw);
                state = 1;
            }
            else
            {
                cw = append_char(cw, *line);
            }
        }
        else
        {
            ft_dprintf(2, "*** INVALID STATE %d\n", state);
            break;
        }
        line++;
    }
    if (key != NULL)
        free(key);
    key = NULL;
    if (cw != NULL)
        free(cw);
    cw = NULL;
    if (error_flag)
    {
        ft_lstclear(&words, free);
        ft_dprintf(2, "* Invalid input\n");
        return (NULL);
    }
    return (words);
}
static void print_string(void *p)
{
    ft_printf("[%s]\n", (char *)p);
}
t_pipeline *minishell_parse_words(t_minishell *ctx, t_list *words)
{
    t_pipeline  *pipeline;

    if (ctx == NULL || words == NULL)
        return (NULL);
    pipeline = NULL; // TODO
    ft_lstiter(words, print_string);
    return (pipeline);
}