#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char buff[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	int			b_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || FOPEN_MAX < fd)
		return (NULL);
	line = NULL;
	while (1)
	{
		if (buff[fd][0] == '\0')
		{
			b_read = read(fd, buff[fd], BUFFER_SIZE);
			if (b_read < 0 && line)
				return (free(line), NULL);
			if (b_read == 0 || (b_read < 0 && !line))
				return (line);
			buff[fd][b_read] = '\0';
		}
		line = ft_strjoin_gnl(line, buff[fd]);
		if (!line)
			return (NULL);
		if (cut_remaining(buff[fd]))
			break ;
	}
	return (line);
}
