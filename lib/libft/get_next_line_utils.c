/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:29:31 by mvassall          #+#    #+#             */
/*   Updated: 2025/02/05 15:05:42 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include "libft.h"

static char	*gnl_calloc(size_t n)
{
	char	*buf;
	char	*p;

	if (n == 0)
		return (NULL);
	buf = malloc(n * sizeof(char));
	if (buf != NULL)
	{
		p = buf;
		while (n-- > 0)
			*p++ = 0;
	}
	return (buf);
}

char	*gnl_get_line_array(t_tlist *frags)
{
	size_t	total_lenght;
	ssize_t	nl_pos;

	total_lenght = 0;
	while (frags != NULL)
	{
		nl_pos = gnl_fragchr(frags, '\n');
		if (nl_pos < 0)
			total_lenght += frags->count;
		else
		{
			total_lenght += nl_pos + 1;
			break ;
		}
		frags = frags->next;
	}
	return (gnl_calloc(total_lenght + 1));
}

t_tlist	*gnl_get_last_frag(t_tlist *frags)
{
	if (frags == NULL)
		return (NULL);
	while (frags->next != NULL)
		frags = frags->next;
	return (frags);
}

// returns the index of the first char c found, else -1
ssize_t	gnl_fragchr(t_tlist *frag, char c)
{
	ssize_t	i;

	if (frag == NULL)
		return (-1);
	i = 0;
	while (i < frag->count)
	{
		if (frag->buf[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*gnl_memmove(char *dst, const char *src, size_t n)
{
	char		*d;
	const char	*s;

	if (n == 0)
		return (dst);
	if (src < dst)
	{
		d = (char *)dst + n - 1;
		s = (const char *)src + n - 1;
		while (n--)
			*d-- = *s--;
	}
	else
	{
		d = (char *)dst;
		s = (const char *)src;
		while (n--)
			*d++ = *s++;
	}
	return (dst);
}
