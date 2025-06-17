/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmap5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:24:13 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/17 19:19:37 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include "libft.h"
#include <stddef.h>

t_result split_key_value(char *str, t_entry *entry)
{
    char *delim;
    char *str_dup;
    t_entry *e;

    if (str == NULL || entry == NULL)
        return (OP_INVALID);
    delim = ft_strchr(str, '=');
    if (delim == NULL)
        return (OP_FAILED);
    str_dup = ft_strdup(str);
    if (str_dup == NULL)
        return (OP_FAILED);
    str_dup[delim - str] = '\0';
    e = entry_create(str_dup, delim + 1, NULL);
    if (e == NULL)
    {
        free(str_dup);
        return (OP_FAILED);
    }
    entry->key = e->key;
    entry->value = e->value;
    free(str_dup);
    free(e);
    return (OP_OK);
}

int ft_is_str_identifier(char *str)
{
    if (str == NULL || *str == '\0')
        return (0);
    if (*str != '_' && !ft_isalpha(*str))
        return (0);
    while (*++str)
        if (*str != '_' && !ft_isalnum(*str))
            return (0);
    return (1);
}