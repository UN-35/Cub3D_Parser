/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelansa <yoelansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:58:54 by yoelansa          #+#    #+#             */
/*   Updated: 2023/12/16 16:15:01 by yoelansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// the func check if there is a new line or not:
//	-if it is exist it should return the index value
//	 (the index which the \n found).
//	-if not it should return a negative value (-1 in that case).

int	line_check(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
// now we should print the line we got.

char	*print_line(char **str)
{
	int		i;
	char	*return_line;
	char	*tmp_str;
	char	*return_str;

	i = line_check (*str);
	if (i < 0)
	{
		return_line = ft_substr (*str, 0, ft_strlen(*str) - 1);
		free (*str);
		*str = NULL;
		return (return_line);
	}
	return_line = ft_substr (*str, 0, i);
	tmp_str = ft_substr (*str, i + 1, ft_strlen(*str) - 1);
	free (*str);
	*str = tmp_str;
	return_str = ft_strtrim(return_line, "\n");
	if (return_line)
		free(return_line);
	return (return_str);
}
// when we allocate a block we should free it and reset it to NULL;
// we dont want any leak tho.

char	*_free(char *cpy, char **str)
{
	if (*str)
	{
		free (*str);
		*str = NULL;
	}
	free (cpy);
	return (NULL);
}

char	*get_next_line(int fd)
{
	ssize_t		i;
	char		*cpy;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	cpy = malloc (sizeof(char) * BUFFER_SIZE + 1);
	if (!cpy)
		return (NULL);
	i = 1;
	while (line_check(str) == -1 && i > 0)
	{
		i = read (fd, cpy, BUFFER_SIZE);
		if (i < 0)
			return (_free(cpy, &str));
		cpy[i] = '\0';
		str = ft_strjoin(str, cpy);
		if (!str)
			return (_free(cpy, &str));
		if (!str[0])
			return (_free(cpy, &str));
	}
	free (cpy);
	return (print_line (&str));
}
