/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:26:32 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/05 17:43:55 by mvassall         ###   ########.fr       */
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
        ft_dprintf(2, "Closing apostrophe missing 1_6\n");
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
        ft_dprintf(2, "Closing quotation mark missing 1_7\n");
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

int parser1_8(t_parser_i *pi, int last_status)
{
    char    *digits;

    if (*pi->cchar == '\0')
    {
        ft_dprintf(2, "Closing quotation mark missing 1_8\n");
        return (-1);
    }
    if (*pi->cchar == '?')
    {
        digits = ft_itoa(last_status);
        append_cw_string(pi, digits);
        free(digits);
        return (7);
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
        ft_dprintf(2, "Closing quotation mark missing 1_9\n");
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
    pi->cchar--;
    return (7);
}
