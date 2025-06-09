/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:37:14 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/09 15:44:49 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_MAP_H
# define HASH_MAP_H
# include "libft.h"
typedef struct s_entry
{
    char            *key;
    char            *value;
    int             is_export;
    struct s_entry  *next;
} t_entry;

typedef enum e_result
{
    OP_OK,
    OP_FAILED,
    OP_INVALID
} t_result;

typedef struct s_hmap
{
    t_entry     **entries;
    unsigned    n_entries;
    unsigned    (*hash_func)(char *key);
}   t_hmap;

t_entry *entry_create(char *key, char *value, t_entry *next);
t_result    entry_destroy(t_entry *e);
t_hmap  *hmap_create(unsigned int init_capacity, unsigned int (*f)(char *key));
void    hmap_destroy(t_hmap *hm);
char    *hmap_lookup(t_hmap *hm, char *key);
t_result    hmap_put(t_hmap *hm, char *key, char *value);
void    hmap_dump(int fd, t_hmap *hm);
t_result    hmap_delete(t_hmap *hm, char *key);
unsigned int hmap_size(t_hmap *hm);
unsigned int default_hash_func(char *txt);
void hmap_export_entry(t_hmap *hm, char *key);
char *hmap_join_key_value(t_entry *e);
char **hmap_to_envp(t_hmap *hm);
t_list *hmap_to_lst(t_hmap *hm);
char **hmap_lst_to_envp(t_list *var_lst);
#endif