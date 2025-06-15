/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmap2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:24:00 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/15 20:31:20 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hmap.h"
#include <stdint.h>

t_result    hmap_put(t_hmap *hm, char *key, char *value)
{
    unsigned int    index;
    t_entry         *entry;

    if (hm == NULL || key == NULL || value == NULL)
        return (OP_INVALID);
    index = hm->hash_func(key) % hm->n_entries;
    entry = hm->entries[index];
    while (entry != NULL)
    {
        if (ft_strcmp(entry->key, key) == 0)
        {
            free(entry->value);
            entry->value = ft_strdup(value);
            if (entry->value == NULL)
                return (OP_FAILED);
            return (OP_OK);
        }
        entry = entry->next;
    }
    hm->entries[index] = entry_create(key, value, hm->entries[index]);
    if (hm->entries[index] == NULL)
        return (OP_FAILED);
    return (OP_OK);
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
static t_result    hmap_del_entry(t_entry *entry, char *key)
{
    t_entry *aux;

    while (entry != NULL && entry->next != NULL)
    {
        if (ft_strcmp(entry->next->key, key) == 0)
        {
            aux = entry->next->next;
            entry_destroy(entry->next);
            entry->next = aux;
            return (OP_OK);
        }
        entry = entry->next;
    }
    return (OP_OK);
}

t_result    hmap_delete(t_hmap *hm, char *key)
{
    unsigned int index;
    t_entry *entry;

    if (hm == NULL || key == NULL)
        return (OP_INVALID);
    index = hm->hash_func(key) % hm->n_entries;
    entry = hm->entries[index];
    if (entry == NULL)
        return (OP_OK);
    if (ft_strcmp(entry->key, key) == 0)
    {
        hm->entries[index] = entry->next;
        return (entry_destroy(entry));
    }
    return (hmap_del_entry(entry, key));
}

unsigned int hmap_size(t_hmap *hm)
{
    unsigned int    count;
    unsigned int    i;
    t_entry         *entry;

    if (hm == NULL || hm->n_entries == 0)
        return (0);
    count = 0;
    i = 0;
    while (i < hm->n_entries)
    {
        entry = hm->entries[i];
        while (entry != NULL)
        {
            count++;
            entry = entry->next;
        }
        i++;
    }
    return (count);
}
