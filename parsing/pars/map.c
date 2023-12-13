
#include "../../cub3d.h"

char	*extract_map_content(t_data **data, char *line, int fd, char *path)
{
	char	*buff;
	int		fd2;

	(*data)->map = malloc(sizeof(char *) * (map_size(data, line, fd) + 1));
	if (!(*data)->map)
		return (ft_error("Map Allocation Failed\n"), exit(1), NULL);
	fd2 = open(path, O_RDONLY);
	if (fd2 < 0)
		return (ft_error("File not opened\n"), exit(1), NULL);
	buff = get_next_line(fd2);
	while (buff)
	{
		if (*(buff + skip_spcs(buff)) == '1')
			cpy_map_content(data, buff, fd2);
		else
		{
			if (buff)
				free(buff);
		}
		buff = get_next_line(fd2);
	}
	return (NULL);
}
