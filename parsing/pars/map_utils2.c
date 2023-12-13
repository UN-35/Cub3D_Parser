
#include "../../cub3d.h"

/* check if surrounded by walls */
int	check_surrounds(t_data *data, int i, int j)
{
	int		len;
	char	**map;

	len = ft_strlen(data->map[i]);
	map = data->map;
	if (map[i][j] == '0' || map[i][j] == 'N'
		|| map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'S')
	{
		if (i == 0 || j == 0 || i == data->map_height - 1 || j == len - 1)
			return (ft_error("Not surrounded by walls\n"), exit(1), 1);
		if ((j > (int)ft_strlen(map[i - 1]))
			|| (j > (int)ft_strlen(map[i + 1])))
			return (ft_error("Not surrounded by walls\n"), exit(1), 1);
		if (map[i][j + 1] == '\0' || map[i - 1][j] == '\0'
			|| map[i + 1][j] == '\0')
			return (ft_error("Not surrounded by walls\n"), exit(1), 1);
		if (map[i][j - 1] == ' ' || map[i][j + 1] == ' '
			|| map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
			return (ft_error("Not surrounded by walls\n"), exit(1), 1);
	}
	return (EXIT_SUCCESS);
}

/* find player position and count invalid players */
int	find_and_count_players(t_data *map, int i, int j)
{
	int		count;
	char	c;

	i = -1;
	count = 0;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			check_surrounds(map, i, j);
			c = map->map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				count ++;
				map->p_x = j;
				map->p_y = i;
			}
		}
	}
	if (count != 1)
		return (ft_error("Player count must be 1\n"), exit(1), 1);
	if (!is_wall(map->map[--i]))
		return (ft_error("Map must be surrounded by walls\n"), exit(1), 1);
	return (EXIT_SUCCESS);
}

/* check for composed characters (0, 1, N, S, E, W) */
int	is_content_valid(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

/* check if it is a wall */
int	is_wall(char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] != '1' && map[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

/* check if all previous data is filled */
int	is_filled(t_data *data)
{
	if (!data)
		return (0);
	if (!data->no || !data->so || !data->we || !data->ea)
		return (0);
	else if (*data->no && *data->so && *data->we && *data->ea
		&& data->f[0] != -1 && data->c[0] != -1)
		return (1);
	return (0);
}
