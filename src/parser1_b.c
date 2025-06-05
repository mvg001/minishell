/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:26:32 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/05 11:45:46 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include "libft.h"
#include "minishell.h"

int parser1_5(t_parser_i *pi, t_hmap *hm)
{
    if (*pi->cchar == '_' || ft_isalnum(*pi->cchar))
    {
        pi->key = append_char(pi->key, *pi->cchar);
        return (5);
    }
    pi->cchar--;
    append_cw_string(pi, hmap_lookup(hm, pi->key));
    free(pi->key);
    pi->key = NULL;
    return (1);
}

int parser1_6(t_parser_i *pi)
{
    if (*pi->cchar == '\0')
    {
        ft_dprintf(2, "Closing apostrophe missing\n");
        return (-1);
    }
    if (*pi->cchar == '\'')
        return (1);
    append_cw_char(pi, *pi->cchar);
    return (6);
}

int parser1_7(t_parser_i *pi)
{
    if (*pi->cchar == '\0')
    {
        ft_dprintf(2, "Closing quotation mark missing\n");
        return (-1);
    }
    if (*pi->cchar == '$')
    {
        pi->key = NULL;
        return (8);
    }
    if (*pi->cchar == '"')
        return (1);
    append_cw_char(pi, *pi->cchar);
    return (7);
}

int parser1_8(t_parser_i *pi)
{
    if (*pi->cchar == '\0')
    {
        ft_dprintf(2, "Closing quotation mark missing\n");
        return (-1);
    }
    if (is_first_char_identifier(*pi->cchar))
    {
        pi->key = append_char(pi->key, *pi->cchar);
        return (9);
    }
    append_cw_char(pi, '$');
    pi->cchar--;
    return (7);
}

int parser1_9(t_parser_i *pi, t_hmap *hm)
{
    if (*pi->cchar == '\0')
    {
        ft_dprintf(2, "Closing quotation mark missing\n");
        return (-1);
    }
    if (*pi->cchar == '_' || ft_isalnum(*pi->cchar))
    {
        pi->key = append_char(pi->key, *pi->cchar);
        return (9);
    }
    append_cw_string(pi, hmap_lookup(hm, pi->key));
    free(pi->key);
    pi->key = NULL;
    return (7);
}