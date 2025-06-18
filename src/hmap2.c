/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmap2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:24:00 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/18 09:50:02 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hmap.h"
#include <stdint.h>

t_result    hmap_put(t_hmap *hm, char *key, char *value)
{
    unsigned int    index;
    t_entry         *entry;
    char            *aux;

    if (hm == NULL || key == NULL || !ft_is_str_identifier(key))
        return (OP_INVALID);
    index = hm->hash_func(key) % hm->n_entries;
    entry = hm->entries[index];
    while (entry != NULL && ft_strcmp(entry->key, key) != 0)
        entry = entry->next;
    if (entry != NULL)
    {
        if (value == NULL)
            return (entry->value = NULL, OP_OK);
        aux = ft_strdup(value);
        if (aux == NULL)
            return (OP_FAILED);
        return (entry->value = aux, OP_OK);
    }
    entry = entry_create(key, value, hm->entries[index]);
    if (entry == NULL)
        return (OP_FAILED);
    return (hm->entries[index] = entry, OP_OK);
}

t_result    hmap_put_entry(t_hmap *hm, char *key, char *value, int is_export)
{
    unsigned int    index;
    t_entry         *entry;
    char            *aux;

    if (hm == NULL || key == NULL || !ft_is_str_identifier(key))
        return (OP_INVALID);
    is_export = is_export != 0;
    index = hm->hash_func(key) % hm->n_entries;
    entry = hm->entries[index];
    while (entry != NULL && ft_strcmp(entry->key, key) != 0)
        entry = entry->next;
    if (entry != NULL)
    {
        if (value == NULL)
            return (entry->value = NULL, entry->is_export = is_export, OP_OK);
        aux = ft_strdup(value);
        if (aux == NULL)
            return (OP_FAILED);
        return (entry->value = aux, entry->is_export = is_export, OP_OK);
    }
    entry = entry_create(key, value, hm->entries[index]);
    if (entry == NULL)
        return (OP_FAILED);
    entry->is_export = is_export;
    return (hm->entries[index] = entry, OP_OK);
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
