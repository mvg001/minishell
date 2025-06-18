/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmap4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:21:21 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/18 09:56:31 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include "libft.h"

static t_result gen_sub_lst(t_list **vars, t_entry *list)
{
    char *var_def;
    t_list  *node;

    while (list != NULL)
    {
        var_def = hmap_join_key_value(list);
        if (var_def == NULL)
            return (OP_FAILED);
        node = ft_lstnew(var_def);
        if (node == NULL)
        {
            free(var_def);
            return (OP_FAILED);
        }
        ft_lstadd_front(vars, node);
        list = list->next;
    }
    return (OP_OK);
}

t_list *hmap_to_lst(t_hmap *hm)
{
    t_list  *var_lst;
    unsigned int i;
    
    if (hm == NULL)
        return (NULL);
    var_lst = NULL;
    i = 0;
    while (i < hm->n_entries)
    {
        if (hm->entries[i] != NULL)
            if (gen_sub_lst(&var_lst, hm->entries[i]) == OP_FAILED)
                break;
        i++;
    }
    if (i < hm->n_entries)
    {
        ft_lstclear(&var_lst, free);
        return (NULL);
    }
    return (var_lst);
}

char **hmap_lst_to_envp(t_list *var_lst)
{
    char **vars;
    int i;

    if (var_lst == NULL)
        return (NULL);
    vars = ft_calloc(ft_lstsize(var_lst) + 1, sizeof(char *));
    if (vars == NULL)
        return (NULL);
    i = 0;
    while (var_lst != NULL)
    {
        vars[i++] = (char *)var_lst->content;
        var_lst = var_lst->next;
    }
    return (vars);
}

t_hmap  *load_env_vars(char **envp)
{
    int count;
    t_hmap  *vars;
    t_entry e;

    if (envp == NULL)
        return (NULL);
    count = ft_split_count(envp);
    if (count <= 0)
        return (NULL);
    vars = hmap_create(count * 2, default_hash_func);
    if (vars == NULL)
        return (NULL);
    while (*envp != NULL)
    {
        if (split_key_value(*envp++, &e) == OP_OK)
        {
            hmap_put_entry(vars, e.key, e.value, 1);
            free(e.key);
            free(e.value);
        }
    }
    return (vars);
}
