/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelansa <yoelansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:01:31 by yoelansa          #+#    #+#             */
/*   Updated: 2023/12/12 10:23:46 by yoelansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// ft_strlen() whiche represent the same behavior of strlen() from string.h 
// "count the number of characters in a string"

// size_t	ft_strlen(char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }
// // ft_substr() take a sub string from a longer or equal string.

// char	*ft_substr(char *s, size_t start, size_t end)
// {
// 	char	*str;
// 	int		i;

// 	if (start > end)
// 		return (NULL);
// 	str = malloc(sizeof(char) * (end - start + 2));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (start <= end)
// 		str[i++] = s[start++];
// 	str[i] = '\0';
// 	return (str);
// }
