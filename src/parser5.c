/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 08:58:11 by user1             #+#    #+#             */
/*   Updated: 2025/06/14 12:47:42 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"

t_list  *expand_words(t_list *words, t_minishell *ctx)
{
    t_list  *output;
    t_list  *new_words;
    int     previous_word_heredoc;
    char    *exp_word;

    output = NULL;
    previous_word_heredoc = 0;
    while (words != NULL)
    {
        ft_dprintf(2, "expand_words next word: [%s]\n", words->content);
        if (previous_word_heredoc)
        {
            previous_word_heredoc = 0;
            ft_lstadd_back(&output, ft_lstnew(ft_strdup(words->content)));
        }
        else if (ft_strcmp(words->content, "<<") == 0)
        {
            previous_word_heredoc = 1;
            ft_lstadd_back(&output, ft_lstnew(ft_strdup("<<")));
        }
        else if (ft_strchr(words->content, '$') != NULL)
        {
            exp_word = expand_word(words->content, ctx);
            if (exp_word != NULL && ft_strcmp(exp_word, words->content) != 0)
            {
                new_words = parser_tokenizer(ctx, exp_word);
                if (new_words != NULL)
                    ft_lstadd_back(&output, new_words);
            }
            else
                ft_lstadd_back(&output, ft_lstnew(ft_strdup(words->content)));
            free(exp_word);
        }
        else
            ft_lstadd_back(&output, ft_lstnew(ft_strdup(words->content)));
        words = words->next;
    }
    return (output);
}
