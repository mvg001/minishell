/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:47:36 by user1             #+#    #+#             */
/*   Updated: 2025/06/04 19:39:49 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "hmap.h"
#include "minishell.h"
#include "libft.h"

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
            state = parser1_1(&words, &cw, &key, *line);
        else if (state == 2)
            state = parser1_2(&words, &cw, &line);
        else if (state == 3)
            state = parser1_3(&words, &cw, &line);
        else if (state == 4)
            state = parser1_4(&cw, &key, &line);
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
