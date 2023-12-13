/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelansa <yoelansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 00:56:16 by yoelansa          #+#    #+#             */
/*   Updated: 2023/12/12 20:26:30 by yoelansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <fcntl.h>
#include "../get_next_line/get_next_line.h"

typedef struct s_parser
{
	char	*n;
	char	*w;
	char	*e;
	char	*s;
	int		floor[3];
	int		ceil[3];
	char	**map;
	int		width;
	int		height;
	// get the player position [x, y];
	// get the width and the height of the map;


}	t_parser;

char	*ft_strrchr(char *s, int c);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strdup(char *src);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, size_t start, size_t end);
size_t	ft_strlen(char *str);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strchr(char *s, int c);
char	**ft_split(char *s, char c);
int	ft_atoi(char *str);
int	ft_isdigit(int c);



#endif