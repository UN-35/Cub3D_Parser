/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelansa <yoelansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 00:58:21 by yoelansa          #+#    #+#             */
/*   Updated: 2023/12/15 16:42:46 by yoelansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_exit_error(char *str)
{
	printf("%s\n", str);
	exit (1);
}


int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int		char_counter(char *str, char c)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			j++;
		i++;
	}
	return (j);
}

void	ft_free(char **str)
{
	int i = -1;
	while (str[++i])
		free(str[i]);
}

int		valid_rgb(char *str)
{
	int i;

	if (!str)
		return (0);
	if (ft_atoi(str) < 0 || ft_atoi(str) > 255)
		return (ft_exit_error("Error : Color must be bitween 0 and 255"), 0);
	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

int		get_colors(t_parser	**data, char *line, int k)
{
	int	i;
	char *str;
	char **rgb;
	
	if (char_counter(line, ',') != 2)
		return (ft_exit_error("Error : Make sure that the color is in RGB format!"), 1);
	line = ft_strtrim(line, " \t");
	rgb = ft_split(ft_strchr(line, ' ') + 1, ',');
	if (!rgb)
		return (0);
	i = -1;
	while (rgb[++i])
	{
		str = ft_strtrim(rgb[i], " \t");
		if (valid_rgb(str))
		{
			if (k)
				(*data)->floor[i] = ft_atoi(str);
			else
				(*data)->ceil[i] = ft_atoi(str);
		}
		else
			return (ft_exit_error("Error : Try valid digits only in RGB format"), 1);
		free(str);
	}
	if (i != 3)
		return (ft_exit_error("Error : Color must be in 3 exact numbers (RGB format)!"), 1);
	return (ft_free(rgb), 0);
}

void	data_initialize(t_parser **data)
{
	(*data)->floor[0] = -1;
	(*data)->ceil[0] = -1;
	(*data)->s = NULL;
	(*data)->e = NULL;
	(*data)->w = NULL;
	(*data)->n = NULL;
	(*data)->width = 0;
	(*data)->height = 0;
	(*data)->map = NULL;
}

int		filename_check_open(char *name)
{
	if (!ft_strrchr(name, '.'))
		return (ft_exit_error("Error: The map name must contain .cub extention!"), 1);
	else if (ft_strncmp(ft_strrchr(name, '.'), ".cub", 4))
		return (ft_exit_error("Error: Wrong extention. Try .cub"), 1);
	return 0;
}

char *pars_direction_name(char *line)
{
	char *path;
	int i;

	i = 0;

	path = ft_strtrim(ft_strchr(ft_strtrim( line, " \t\n"), ' '), " \t\n");
	if (!path)
		ft_exit_error("Error : Empty path!");
	while (path[i])
	{
		if (path[i] == ' ' || path[i] == '\t')
			ft_exit_error("Error : Path must not contain spaces");
		i++;
	}
	if (ft_strncmp(ft_strrchr(path, '.'), ".xpm", 5))
		ft_exit_error("Error : Path must have .xpm extention!");
	return (path);
}

/////////////////////////

int		check_borders(t_parser	*data, int i, int j)
{
	int		len;
	char	**map;

	len = ft_strlen(data->map[i]);
	map = data->map;
	if (map[i][j] == '0' || map[i][j] == 'N'
		|| map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'S')
	{
		if (i == 0 || j == 0 || i == data->height - 1 || j == len - 1)
			return (ft_exit_error("Error : The map must be surrounded by walls (1)!"), 1);
		if (j > (int)ft_strlen(map[i - 1]) || j > (int)ft_strlen(map[i + 1]))	
			return (ft_exit_error("Error : The map must be surrounded by walls (1)!"), 1);
		if (map[i][j + 1] == '\0' || map[i - 1][j] == '\0' || map[i + 1][j] == '\0')
			return (ft_exit_error("Error : The map must be surrounded by walls (1)!"), 1);
		if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ' || map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
			return (ft_exit_error("Error : The map must be surrounded by walls (1)!"), 1);
	}
	return (EXIT_SUCCESS);
}

int		valid_map_content(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != 'N' && str[i] != 'E'
			&& str[i] != 'W' && str[i] != ' ' && str[i] != 'S')
			return (0);
		i++;
	}
	return (1);
}
int		check_wall(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] != '1' && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int		map_info(t_parser **data, char *line, int fd)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	if (!check_wall(line))
		return (ft_exit_error("Error : The map must be surrounded by walls (1)!"), 1);
	while (line)
	{
		i++;
		if (!(*line) || !valid_map_content(line))
		{
			printf("|%s|\n|%c|\n", line, *line);
			return (ft_exit_error("Error : Invalid content"), 1);
		}
		if (line)
			free(line);
		line = get_next_line(fd);
	}
	close (fd);
	line = NULL;
	(*data)->height = i;
	return (i);
}
/////////////////////////
///ap 
///eight 
///
int	get_map_width(char **map, int height)
{
	size_t	width;
	int		i;

	i = 0;
	width = ft_strlen(map[i]);
	while (i < height)
	{
		if (ft_strlen(map[i]) > width)
			width = ft_strlen(map[i]);
		i++;
	}
	return ((int)width);
}

int		check_player(t_parser *data, int i, int j)
{
	int		count;
	char	c;
	
	i = -1;
	count = 0;
	while (data->map[++i])
	{
		// printf("row [%d] -> |%s|\n", i, data->map[i]);
		j = -1;
		while (data->map[i][++j])
		{
			check_borders(data, i, j);
			c = data->map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				count++;
				data->player_x = j;
				data->player_y = i;
			}
		}
	}
	if (count != 1)
		return (ft_exit_error("Error : It must be exactly 1 player!"), 1);
	if (!check_wall(data->map[i - 1]))
		return (ft_exit_error("Error : The map must be surrounded by walls (1)!"), 1);
	return (0);
}

// int		map_content(t_parser **data, int file_d, char *buffer)
// {
// 	int		i;

// 	i = 0;
// 	while(buffer)
// 	{
// 		if (*buffer == '\0')
// 			return (ft_exit_error("Error : Map not found"), 1);
// 		(*data)->map[i] = buffer;
// 		buffer = get_next_line(file_d);
// 		i++;
// 	}
// 	(*data)->map[i] = buffer;
// 	close(file_d);
// 	return (0); 
// }


char	*inside_map(t_parser **data, char *path, char *line, int fd)
{
	char	*buffer;
	int		file_d;
	int		i;
	int		j;


	int alloc = map_info(data, line, fd) + 1;
	
	(*data)->map = malloc(sizeof(char *) * alloc);
	if (!(*data)->map)
		return (ft_exit_error("Error : Malloc failed!"), NULL);
	
	
		
	file_d = open(path, O_RDONLY);
	if (file_d < 0)
		return (ft_exit_error("Error : Failed oppening file!"), NULL);


	buffer = get_next_line(file_d);

	while (buffer)
	{
		if (*buffer == '\0')
		{
			if ( buffer )
				free(buffer);
			buffer = get_next_line(file_d);
			continue;
		}
		i = 0;
		while(buffer[i] == ' ' || buffer[i] == '\t')
			i++;
		if(*(buffer + i) == '1')
		{
			// this is map_content();
			j = 0;
			while(buffer)
			{
				if (*buffer == '\0')
					ft_exit_error("Error : Map not found");
				
				(*data)->map[j] = buffer;
				buffer = get_next_line(file_d);
				j++;
			}
			(*data)->map[j] = buffer;
			close(file_d);
		}
		else
			if(buffer)
				free(buffer);
		buffer = get_next_line(file_d);
	}
	check_player(*data, 0, 0);
	return (NULL);
}

int		data_ready(t_parser *data)
{
	if (!data)
		return (0);
	if (!data->n || !data->w || !data->s || !data->e)
		return (0);
	else if (*data->n && *data->s && *data->w && *data->e
		&& data->floor[0] != -1 && data->ceil[0] != -1)
		return (1);
	return (0);
}

//////////////////





int main(int ac, char  **av)
{
	int fd = 0;
	t_parser	*data;
	char		*line;
	int			i;

	if (ac != 2)
		return (ft_exit_error("Error : Try two arguments.."), 1);
	filename_check_open(av[1]);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_exit_error("Error : Try an exist file"), 1);
	data = malloc(sizeof(t_parser));
	if (!data)
		return (ft_exit_error("Error: Malloc failure!"), 1);
	data_initialize(&data);
	i = 0;
	while (1)
	{
		i = 0;
		line = get_next_line(fd);
		if (!line)
			break ;
		while (is_space(line[i]))
			i++;
		if(line[i] == '\0')
			continue;
		else if (!ft_strncmp(line + i, "NO ", 3) && !data->n)	
			data->n = pars_direction_name(line);
		else if (!ft_strncmp(line + i, "SO ", 3) && !data->s)
			data->s = pars_direction_name(line);
		else if (!ft_strncmp(line + i, "WE ", 3) && !data->w)
			data->w = pars_direction_name(line);
		else if (!ft_strncmp(line + i, "EA ", 3) && !data->e)
			data->e = pars_direction_name(line);
		else if (!ft_strncmp(line + i, "F ", 2) && data->floor[0] == -1)
			get_colors(&data, line, 1);
		else if (!ft_strncmp(line + i, "C ", 2) && data->ceil[0] == -1)
			get_colors(&data, line, 0);
		else if (*(line + i) == '1' && data_ready(data))
			line = inside_map(&data, av[1], line, fd);
		else
			ft_exit_error("Error : A fiew arguments must be missed up!");
		if (line)
			free(line);
	}
	data->width = get_map_width(data->map, data->height);
	printf ("south -> |%s|\nwest -> |%s|\neast -> |%s|\nnorth -> |%s|\nheight -> |%d|\nwidth -> |%d|\n", data->s, data->w, data->e, data->n, data->height, data->width);
}

