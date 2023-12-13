
#include "../../cub3d.h"

/* Calculate map size for allocation + some parsing checks */
int	map_size(t_data **data, char *line, int fd)
{
	int		x;

	x = 0;
	if (!line)
		return (EXIT_FAILURE);
	if (!is_wall(line))
		return (ft_error("Map must be surrounded by walls\n"), exit(1), 1);
	while (line)
	{
		x++;
		if (!*line || !is_content_valid(line))
			return (ft_error("Try map with (0, 1, N, S, E, W)\n"), exit(1), 1);
		if (line)
			free(line);
		line = get_next_line(fd);
	}
	close(fd);
	line = NULL;
	(*data)->map_height = x;
	return (x);
}

/* Cpy Map from file to **map */
int	cpy_map_content(t_data **data, char *line, int fd2)
{
	int	i;

	i = 0;
	while (line)
	{
		if (*line == '\0')
			return (ft_error("Map not copied\n"), exit(1), 1);
		(*data)->map[i] = line;
		line = get_next_line(fd2);
		i++;
	}
	(*data)->map[i] = NULL;
	close(fd2);
	find_and_count_players(*data, 0, 0);
	return (EXIT_SUCCESS);
}

int	calculate_map_width(char **map, int height)
{
	size_t	width;
	int		i;

	i = 0;
	width = ft_strlen(map[i]);
	while (i <= height)
	{
		if (ft_strlen(map[i]) > width)
			width = ft_strlen(map[i]);
		i++;
	}
	return ((int)width);
}
