/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelansa <yoelansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:53:12 by yoelansa          #+#    #+#             */
/*   Updated: 2023/12/16 16:12:31 by yoelansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	map_content(t_parser **data, int file_d, char *buffer)
{
	int	j;

	j = 0;
	while (buffer)
	{
		if (*buffer == '\0')
			ft_exit_error("Error : Map not found");
		(*data)->map[j] = buffer;
		buffer = get_next_line(file_d);
		j++;
	}
	(*data)->map[j] = buffer;
	free(buffer);
	close(file_d);
}

void	look_for_map(t_parser **data, char *buffer, int file_d)
{
	int	i;

	i = 0;
	while (buffer[i] == ' ' || buffer[i] == '\t')
		i++;
	if (*(buffer + i) == '1')
		map_content(data, file_d, buffer);
	else
		if (buffer)
			free(buffer);
}

char	*inside_map(t_parser **data, char *path, char *line, int fd)
{
	char	*buffer;
	int		file_d;

	(*data)->map = malloc(sizeof(char *) * (map_info(data, line, fd) + 1));
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
			if (buffer)
				free(buffer);
			buffer = get_next_line(file_d);
			continue ;
		}
		look_for_map(data, buffer, file_d);
		buffer = get_next_line(file_d);
	}
	check_player(*data, 0, 0);
	(*data)->width = get_map_width((*data)->map, (*data)->height);
	return (NULL);
}

int	free_mystr(char *str)
{
	if (!str)
		return (-1);
	free(str);
	return (1);
}

void	parser_brain( t_parser **d, int *fd, char *l, char *path)
{
	while (l)
	{
		l = get_next_line(*fd);
		if (l && l[cl_s(l)] == '\0' && free_mystr(l))
			continue ;
		else if (l && !ft_strncmp(l + cl_s(l), "NO ", 3) && !(*d)->n)
			(*d)->n = pars_direction_name(l);
		else if (l && !ft_strncmp(l + cl_s(l), "SO ", 3) && !(*d)->s)
			(*d)->s = pars_direction_name(l);
		else if (l && !ft_strncmp(l + cl_s(l), "WE ", 3) && !(*d)->w)
			(*d)->w = pars_direction_name(l);
		else if (l && !ft_strncmp(l + cl_s(l), "EA ", 3) && !(*d)->e)
			(*d)->e = pars_direction_name(l);
		else if (l && !ft_strncmp(l + cl_s(l), "F ", 2) && (*d)->floor[0] < 0)
			get_colors(d, l, 1);
		else if (l && !ft_strncmp(l + cl_s(l), "C ", 2) && (*d)->ceil[0] < 0)
			get_colors(d, l, 0);
		else if (l && *(l + cl_s(l)) == '1' && data_ready((*d)))
			l = inside_map(d, path, l, *fd);
		else
			ft_exit_error("Error : invalid content!");
		free_mystr(l);
	}
	if (!data_ready(*d) || !(*d)->map)
		ft_exit_error("Error : a file must countain subj requirements!");
}
