#ifndef BUFFER_SIZE
# error BUFFER_SIZE not defined
#elif !(BUFFER_SIZE > 0)
# error BUFFER_SIZE not greater than 0
#endif

#include "get_next_line.h"
#include <limits.h>
#include <stdlib.h>

char
	*get_next_line(int fd)
{
	static t_file	files[OPEN_MAX];
	t_line			line;

	if (fd < 0 || fd >= OPEN_MAX)
		return (NULL);
	line.size = 0;
	line.maxsize = 1024;
	line.data = malloc(1024);
	if (line.data == NULL)
		return (NULL);
	if (read_line(fd, &line, &files[fd]) < 0)
	{
		free(line.data);
		return (NULL);
	}
	line.data = ft_realloc(line.data, line.size + 1, line.size);
	if (line.data != NULL)
		line.data[line.size] = '\0';
	return (line.data);
}
