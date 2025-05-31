/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmap3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:15:02 by mvassall          #+#    #+#             */
/*   Updated: 2025/05/29 16:36:44 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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
