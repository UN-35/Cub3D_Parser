/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelansa <yoelansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:19:31 by yoelansa          #+#    #+#             */
/*   Updated: 2023/12/12 20:14:31 by yoelansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parser.h"

int	ft_atoi(char *str)
{
	int	a;
	int	r;
	int	k;

	k = 0;
	a = 1;
	r = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		a *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		r = r * 10 + *str++ - 48;
		k++;
	}
	return (a * r);
}