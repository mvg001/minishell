/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:37:14 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/18 10:02:50 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HMAP_H
# define HMAP_H
# include "libft.h"

typedef struct s_entry
{
	char			*key;
	char			*value;
	int				is_export;
	struct s_entry	*next;
}	t_entry;

typedef enum e_result
{
	OP_OK,
	OP_FAILED,
	OP_INVALID
}	t_result;

typedef struct s_hmap
{
	t_entry			**entries;
	unsigned int	n_entries;
	unsigned int	(*hash_func)(char *key);
}	t_hmap;

// key and value are duplicated
t_entry			*entry_create(char *key, char *value, t_entry *next);
t_entry			*hmap_create_entry(char *key, char *value, int is_export);
t_result		entry_destroy(t_entry *e);
t_hmap			*hmap_create(unsigned int initial_capacity,
					unsigned int (*f)(char *key));
void			hmap_destroy(t_hmap *hm);
char			*hmap_lookup(t_hmap *hm, char *key);
t_result		hmap_put(t_hmap *hm, char *key, char *value);
t_result		hmap_put_entry(t_hmap *hm, char *key, char *value, int is_export);
void			hmap_dump(int fd, t_hmap *hm);
t_result		hmap_delete(t_hmap *hm, char *key);
unsigned int	hmap_size(t_hmap *hm);
unsigned int	default_hash_func(char *txt);
void			hmap_export_entry(t_hmap *hm, char *key);
char			*hmap_join_key_value(t_entry *e);
char			**hmap_to_envp(t_hmap *hm);
t_list			*hmap_to_lst(t_hmap *hm);
char			**hmap_lst_to_envp(t_list *var_lst);
t_hmap			*load_env_vars(char **envp);
t_result		split_key_value(char *env, t_entry *entry);
int				ft_is_str_identifier(char *str);
int				hmap_has_key(t_hmap *hm, char *key);
#endif
