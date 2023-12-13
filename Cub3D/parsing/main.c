/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelansa <yoelansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 00:58:21 by yoelansa          #+#    #+#             */
/*   Updated: 2023/12/13 21:20:43 by yoelansa         ###   ########.fr       */
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
		return (0);
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

char *pars_path_mlx(char *line)
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
	if (ft_strncmp(ft_strrchr(path, '.'), ".mlx", 5))
		ft_exit_error("Error : Path must have .mlx extention!");
	return (path);
}

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
			break;
		while (is_space(line[i]))
			i++;
		if(line[i] == '\0')
			continue;
		else if (!ft_strncmp(line + i, "NO ", 3) && !data->n)	
			data->n = pars_path_mlx(line);
		else if (!ft_strncmp(line + i, "SO ", 3) && !data->s)
			data->s = pars_path_mlx(line);
		else if (!ft_strncmp(line + i, "WE ", 3) && !data->w)
			data->w = pars_path_mlx(line);
		else if (!ft_strncmp(line + i, "EA ", 3) && !data->e)
			data->e = pars_path_mlx(line);
		else if (!ft_strncmp(line + i, "F ", 2) && data->floor[0] == -1)
			get_colors(&data, line, 1);
		else if (!ft_strncmp(line + i, "C ", 2) && data->ceil[0] == -1)
			get_colors(&data, line, 0);
		else
			ft_exit_error("Error : A fiew arguments must be missed up!");
		if (line)
			free(line);
	}
	printf("%s\n%s\n%s\n%s\n", data->n, data->e, data->w, data->s);
}

