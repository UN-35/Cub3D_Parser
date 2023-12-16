/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelansa <yoelansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 10:12:43 by yoelansa          #+#    #+#             */
/*   Updated: 2023/12/16 16:12:35 by yoelansa         ###   ########.fr       */
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

int	char_counter(char *str, char c)
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
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

int	cl_s(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (is_space(str[i]))
		i++;
	return (i);
}
