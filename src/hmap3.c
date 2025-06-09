/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmap3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:15:02 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/09 14:20:57 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "hmap.h"

unsigned int default_hash_func(char *txt)
{
    unsigned int    prime;
    unsigned int    n;

    prime = 31;
    n = 1;
    while (*txt)
    {
        n = n * prime + (unsigned int)*txt;
        txt++;
    }
    return (n);
}

void hmap_export_entry(t_hmap *hm, char *key)
{
    unsigned int    index;
    t_entry         *entry;

    if (hm == NULL || key == NULL)
        return ;
    index = hm->hash_func(key) % hm->n_entries;
    entry = hm->entries[index];
    if (entry == NULL)
        return ;
    while (entry != NULL)
    {
        if (ft_strcmp(entry->key, key) == 0)
        {
            entry->is_export = 1;
            return ;
        }
        entry = entry->next;
    }
    return ;
}

char *hmap_join_key_value(t_entry *e)
{
    unsigned int len;
    char *output;

    if (e == NULL)
        return (NULL);
    len = ft_strlen(e->key) + 2;
    len += ft_strlen(e->value);
    output = ft_calloc(1, len * sizeof(char));
    if (output == NULL)
        return (NULL);
    ft_strlcpy(output, e->key, len);
    ft_strlcat(output, "=", len);
    ft_strlcat(output, e->value, len);
    return (output);
}

static int envp_1(t_hmap *hm, char **envp, unsigned int i, unsigned int j)
{
    t_entry *e;

    while (i < hm->n_entries)
    {
        e = hm->entries[i];
        while (e != NULL)
        {
            if (e->is_export)
            {
                envp[j] = hmap_join_key_value(e);
                if (envp[j] == NULL)
                    return (0);
                j++;
            }
            e = e->next;
        }
        i++;
    }
    return (1);
}

char **hmap_to_envp(t_hmap *hm)
{
    char **envp;

    if (hm == NULL)
        return (NULL);
    envp = ft_calloc(hmap_size(hm) + 1, sizeof(char *));
    if (envp == NULL)
        return (NULL);
    if (envp_1(hm, envp, 0, 0) == 0)
        return (ft_dispose_split(envp));
    return (envp);
}
