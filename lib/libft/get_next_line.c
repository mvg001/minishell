/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:29:31 by mvassall          #+#    #+#             */
/*   Updated: 2025/05/21 16:28:35 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "libft.h"

static t_tlist	*read_frag(int fd)
{
	t_tlist	*f;

	f = malloc(sizeof(t_tlist));
	if (f == NULL)
		return (NULL);
	f->next = NULL;
	f->count = read(fd, f->buf, BUFFER_SIZE);
	if (f->count <= 0)
	{
		free(f);
		return (NULL);
	}
	return (f);
}

static t_tlist	*read_frags(int fd, t_tlist *frags)
{
	t_tlist	*frag;
	t_tlist	*last_frag;

	while (1)
	{
		last_frag = gnl_get_last_frag(frags);
		if (last_frag != NULL && gnl_fragchr(last_frag, '\n') >= 0)
			return (frags);
		frag = read_frag(fd);
		if (frag == NULL)
			return (frags);
		if (last_frag == NULL)
			frags = frag;
		else
			last_frag->next = frag;
	}
}

static t_tlist	*get_line_aux(t_tlist *frags, char *line)
{
	ssize_t	nl_i;
	t_tlist	*next;

	nl_i = -1;
	while (frags != NULL && nl_i < 0)
	{
		nl_i = gnl_fragchr(frags, '\n');
		if (nl_i >= 0)
		{
			line = gnl_memmove(line, frags->buf, nl_i + 1) + (nl_i + 1);
			if (nl_i < frags->count - 1)
			{
				frags->count -= (nl_i + 1);
				gnl_memmove(frags->buf, frags->buf + (nl_i + 1), frags->count);
				break ;
			}
		}
		else
			line = gnl_memmove(line, frags->buf, frags->count) + frags->count;
		next = frags->next;
		free(frags);
		frags = next;
	}
	return (frags);
}

static char	*get_line(t_tlist **frags)
{
	char	*line;

	if (frags == NULL || *frags == NULL)
		return (NULL);
	line = gnl_get_line_array(*frags);
	if (line == NULL)
		return (NULL);
	*frags = get_line_aux(*frags, line);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_tlist	*frag_list[MAX_FD];
	t_tlist			*next;
	t_tlist			*f;
	char			*next_line;

	if (fd < 0 || fd >= MAX_FD)
		return (NULL);
	frag_list[fd] = read_frags(fd, frag_list[fd]);
	if (frag_list[fd] == NULL)
		return (NULL);
	next_line = get_line(frag_list + fd);
	if (next_line == NULL && frag_list[fd] != NULL)
	{
		f = frag_list[fd];
		while (f != NULL)
		{
			next = f->next;
			free(f);
			f = next;
		}
		frag_list[fd] = NULL;
	}
	return (next_line);
}
