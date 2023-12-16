/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelansa <yoelansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:23:43 by yoelansa          #+#    #+#             */
/*   Updated: 2023/12/16 16:15:50 by yoelansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parser.h"

char	*ft_strdup(char *src)
{
	int		i;
	char	*dest;

	dest = malloc(ft_strlen(src) + 1);
	if (!dest)
		return (0);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
