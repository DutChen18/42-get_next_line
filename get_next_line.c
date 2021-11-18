#ifndef BUFFER_SIZE
# error BUFFER_SIZE not defined
#elif !(BUFFER_SIZE > 0)
# error BUFFER_SIZE not greater than 0
#endif

#include "get_next_line.h"
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

char
	*ft_realloc(char *oldptr, size_t newsize, size_t oldsize)
{
	char	*newptr;

	newptr = malloc(newsize);
	if (newptr == NULL)
	{
		free(oldptr);
		return (NULL);
	}
	while (0 < oldsize)
	{
		oldsize -= 1;
		newptr[oldsize] = oldptr[oldsize];
	}
	return (newptr);
}

int
	push_char(char ch, t_line *line)
{
	if (line->size == line->maxsize)
	{
		line->data = ft_realloc(line->data, line->maxsize * 2, line->maxsize);
		line->maxsize *= 2;
		if (line->data == NULL)
			return (-1);
	}
	line->data[line->size] = ch;
	line->size += 1;
	return (0);
}

int
	read_line(int fd, t_line *line, t_file *file)
{
	ssize_t	size;

	while (1)
	{
		if (file->offset >= file->size)
		{
			size = read(fd, file->buffer, BUFFER_SIZE);
			if (size <= 0)
				return (-(!line->size || size < 0));
		}
		if (push_char(file->buffer[file->offset], line) < 0)
			return (-1);
		file->offset += 1;
		if (line->data[line->size - 1] == '\n')
			return (0);
	}
}

char
	*get_next_line(int fd)
{
	static t_file	files[OPEN_MAX];
	t_line			line;

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
