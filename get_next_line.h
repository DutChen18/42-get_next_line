#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifdef BUFFER_SIZE
#  include <stddef.h>
typedef struct s_file	t_file;
typedef struct s_line	t_line;

struct s_file
{
	size_t	offset;
	size_t	size;
	char	buffer[BUFFER_SIZE];
};

struct s_line
{
	size_t	size;
	size_t	maxsize;
	char	*data;
};
# endif

char	*get_next_line(int fd);

#endif
