/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmap1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:59:53 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/19 13:51:08 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "hmap.h"
#include "libft.h"

t_entry *entry_create(char *key, char *value, t_entry *next)
{
    t_entry *e;

    if (key == NULL || !ft_is_str_identifier(key))
        return (NULL);
    e = ft_calloc(1, sizeof(t_entry));
    if (e == NULL)
        return (NULL);
    e->key = ft_strdup(key);
    if (e->key == NULL)
        return (free(e), NULL);
    e->value = NULL;
    if (value != NULL)
        e->value = ft_strdup(value);
    if (e->value == NULL && value != NULL)
        return (free(e->key), free(e), NULL);
    e->is_export = 0;
    e->next = next;
    return (e);
}

t_entry *hmap_create_entry(char *key, char *value, int is_export)
{
    t_entry *e;

    e = entry_create(key, value, NULL);
    if (e == NULL)
        return (NULL);
    e->is_export = is_export;
    return (e);
}

t_result    entry_destroy(t_entry *e)
{
    if (e == NULL)
        return (OP_INVALID);
    if (e->key != NULL)
        free(e->key);
    if (e->value != NULL)
        free(e->value);
    free(e);
    return (OP_OK);
}

t_hmap  *hmap_create(unsigned int init_capacity, unsigned int (*f)(char *key))
{
    t_hmap *hm;

    if (init_capacity == 0 || f == NULL)
        return (NULL);
    hm = (t_hmap *)ft_calloc(1, sizeof(t_hmap));
    if (hm == NULL)
        return (NULL);
    hm->hash_func = f;
    hm->n_entries = init_capacity;
    hm->entries = ft_calloc(init_capacity, sizeof(t_entry *));
    if (hm->entries == NULL)
    {
        free(hm);
        hm = NULL;
    }
    return (hm);
}

void    hmap_destroy(t_hmap *hm)
{
    unsigned int    i;
    t_entry         *e;
    t_entry         *e_next;

    if (hm == NULL || hm->n_entries == 0)
        return ;
    i = 0;
    while (i < hm->n_entries)
    {
        e = hm->entries[i];
        while (e != NULL)
        {
            e_next = e->next;
            entry_destroy(e);
            e = e_next;
        }
        i++;
    }
    free(hm->entries);
    free(hm);
}
