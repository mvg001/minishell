/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:47:45 by mvassall          #+#    #+#             */
/*   Updated: 2025/06/09 20:20:26 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

static char *ft_loop_file(int fd, t_buf *rb)
{
    char *line;
    char *ppid_line;

    ppid_line = NULL;
    while (1)
    {
        line = gnl_getline(fd, rb);
        if (line == NULL)
            break;
        if (ft_strncmp(line, "PPid:", 5) == 0)
        {
            ppid_line = line;
            break;
        }
        free(line);
    }
    return (ppid_line);
}

static char *read_ppid_line()
{
    int fd;
    t_buf *rb;
    char    *ppid_line;
    
    fd = open("/proc/self/status", O_RDONLY);
    if (fd < 0)
        return NULL;
    rb = gnl_alloc_buf(1024);
    if (rb == NULL)
    {
        close(fd);
        return (NULL);
    }
    ppid_line = ft_loop_file(fd, rb);
    gnl_dispose(rb);
    close(fd);
    return (ppid_line);
}

int ft_getpid()
{
    char *ppid_line;
    char *colon_ptr;
    int pid;

    ppid_line = read_ppid_line();
    if (ppid_line == NULL)
        return (-1);
    pid = -1;
    colon_ptr = ft_strchr(ppid_line, ':');
    if (colon_ptr != NULL)
        pid = ft_atoi(colon_ptr + 1);
    free(ppid_line);
    return (pid);
}
