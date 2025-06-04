/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:26:32 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/04 19:38:45 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include "libft.h"
#include "minishell.h"

int parser1_5(t_minishell *ctx, char **cw, char **key, char **c)
{
    if (**c == '_' || ft_isalnum(**c))
    {
        *key = append_char(*key, **c);
        return (5);
    }
    (*c)--;
    *cw = append_string(*cw, hmap_lookup(ctx->vars, *key));
    free(*key);
    *key = NULL;
    return (1);
}