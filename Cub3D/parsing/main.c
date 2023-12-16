/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelansa <yoelansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 00:58:21 by yoelansa          #+#    #+#             */
/*   Updated: 2023/12/16 16:23:07 by yoelansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_printer(t_parser *data)
{
	int	i;

	i = 0;
	printf("South : '%s'\n", data->n);
	printf("South : '%s'\n", data->w);
	printf("South : '%s'\n", data->e);
	printf("South : '%s'\n\n", data->s);
	printf("Floor (");
	for (i = 0; i < 3; i++)
	{
		printf("%d", data->floor[i]);
		if (i < 2)
			printf(",");
	}
	printf(")\nCeil (");
	for (i = 0; i < 3; i++)
	{
		printf("%d", data->ceil[i]);
		if (i < 2)
			printf(",");
	}
	printf(")\n\nHeight : '%d'", data->height);
	printf("\nWidth : '%d'\n", data->width);
}

int	main(int ac, char **av)
{
	int			fd;
	t_parser	*data;
	char		*line;

	if (ac != 2)
		return (ft_exit_error("Error : Try two arguments.."), 1);
	filename_check_open(av[1], &fd);
	data = malloc(sizeof(t_parser));
	if (!data)
		return (ft_exit_error("Error: Malloc failure!"), 1);
	data_initialize(&data);
	line = "";
	parser_brain(&data, &fd, line, av[1]);
	// system("leaks cub3d");
	ft_printer(data);
}
