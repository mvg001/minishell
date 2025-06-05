#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

int main(void) {
    int fd = open("/proc/self/status", O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "unable to open file /proc/self/status\n");
        return 1;
    }
    t_buf *rb = gnl_alloc_buf(1024);
    if (rb != NULL) {
        char *line;
        while (1) {
            line = gnl_getline(fd, rb);
            if (line == NULL)
                break;
            if (ft_strncmp(line, "PPid:", 5) == 0) {
                printf("%s", line);
                free(line);
                line = NULL;
                break;
            }
            free(line);
            line = NULL;
        }
        gnl_dispose(rb);
    }
    close(fd);
    return 0;
}