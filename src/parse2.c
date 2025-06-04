/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:24:11 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/04 18:24:45 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
