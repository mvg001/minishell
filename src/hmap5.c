/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmap5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:24:13 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/18 13:56:04 by user1            ###   ########.fr       */
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

int	hmap_has_key(t_hmap *hm, char *key)
{
    unsigned int    index;
    t_entry         *entry;

    if (hm == NULL || key == NULL)
        return (0);
    index = hm->hash_func(key) % hm->n_entries;
    entry = hm->entries[index];
    if (entry == NULL)
        return (0);
    while (entry != NULL)
    {
        if (ft_strcmp(entry->key, key) == 0)
            return (1);
        entry = entry->next;
    }
    return (0);
}

char    *hmap_lookup(t_hmap *hm, char *key)
{
    unsigned int    index;
    t_entry         *entry;

    if (hm == NULL || key == NULL)
        return (NULL);
    index = hm->hash_func(key) % hm->n_entries;
    entry = hm->entries[index];
    if (entry == NULL)
        return (NULL);
    while (entry != NULL)
    {
        if (ft_strcmp(entry->key, key) == 0)
            return (ft_strdup(entry->value));
        entry = entry->next;
    }
    return (NULL);
}

void    hmap_dump(int fd, t_hmap *hm)
{
    unsigned int    index;
    unsigned int    size;
    t_entry         *entry;

    if (fd < 0 || hm == NULL)
        return ;
    size = hmap_size(hm);
    ft_dprintf(fd, "size = %u\n", size);
    index = 0;
    while (index < hm->n_entries)
    {
        entry = hm->entries[index];
        if (entry != NULL)
            ft_dprintf(fd, "index = %d\n", index);
        while (entry != NULL)
        {
            ft_dprintf(fd, "\t'%s' => '%s', is_export %d\n",
                entry->key, entry->value, entry->is_export);
            entry = entry->next;
        }
        index++;
    }
}
