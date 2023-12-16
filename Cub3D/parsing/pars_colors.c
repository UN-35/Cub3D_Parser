/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelansa <yoelansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 09:17:29 by yoelansa          #+#    #+#             */
/*   Updated: 2023/12/16 14:55:06 by yoelansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	valid_rgb(char *str)
{
	int	i;

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

char	**get_rgb(char *line)
{
	char	**rgb;

	if (char_counter(line, ',') != 2)
		return (ft_exit_error
			("Error : Make sure the color is in RGB format!"), exit(1), NULL);
	line = ft_strtrim(line, " \t");
	rgb = ft_split(ft_strchr(line, ' ') + 1, ',');
	if (!rgb)
		return (NULL);
	free(line);
	return (rgb);
}

int	get_colors(t_parser	**data, char *line, int k)
{
	int		i;
	char	*str;
	char	**rgb;

	i = -1;
	rgb = get_rgb(line);
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
			return (ft_exit_error
				("Error : Try valid digits only in RGB format"), 1);
		free(str);
	}
	if (i != 3)
		return (ft_exit_error
			("Error : Color must be in 3 exact numbers (RGB format)!"), 1);
	return (ft_free(rgb), 0);
}
