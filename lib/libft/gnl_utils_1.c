/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user1 <user1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:29:31 by mvassall          #+#    #+#             */
/*   Updated: 2025/03/07 11:32:27 by user1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

size_t	gnl_strlen(char *str)
{
	size_t	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	*gnl_dispose(t_buf *sb)
{
	if (sb == NULL)
		return (NULL);
	if (sb->buf != NULL)
		free(sb->buf);
	free(sb);
	return (NULL);
}

t_buf	*gnl_alloc_buf(unsigned int buffer_size)
{
	t_buf	*sb;

	if (buffer_size == 0)
		return (NULL);
	sb = malloc(sizeof(t_buf));
	if (sb == NULL)
		return (NULL);
	sb->buf = malloc((buffer_size + 1) * sizeof(char));
	if (sb->buf == NULL)
		return (gnl_dispose(sb));
	sb->buf[0] = '\0';
	sb->start = NULL;
	sb->buffer_size = buffer_size;
	sb->ungetc = 0;
	return (sb);
}

char	*get_next_line(int fd)
{
	static t_buf	*tb[MAX_FD];
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (tb[fd] == NULL)
		tb[fd] = gnl_alloc_buf(BUFFER_SIZE);
	line = gnl_getline(fd, tb[fd]);
	if (line == NULL)
	{
		gnl_dispose(tb[fd]);
		tb[fd] = NULL;
	}
	return (line);
}

int	gnl_getchar(int fd, t_buf *rb)
{
	int	c;

	if (fd < 0 || rb == NULL)
		return (-2);
	if (rb->start == NULL || *rb->start == '\0')
		if (gnl_read_buf(fd, rb) <= 0)
			return (-1);
	c = *rb->start;
	rb->start++;
	return (c);
}
