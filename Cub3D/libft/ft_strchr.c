/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelansa <yoelansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:41:51 by yoelansa          #+#    #+#             */
/*   Updated: 2023/12/12 14:50:39 by yoelansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parser.h"

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	*str;

	if (!s)
		return NULL;
	str = (char *)s;
	i = 0;
	while (str[i] != (char) c)
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (str + i);
}
