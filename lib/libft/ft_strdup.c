/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:35:26 by mvassall          #+#    #+#             */
/*   Updated: 2024/12/11 11:46:54 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(str);
	dup = (char *)malloc(sizeof(*dup) * (len + 1));
	if (dup == NULL)
		return (NULL);
	return (ft_memcpy(dup, str, len + 1));
}
