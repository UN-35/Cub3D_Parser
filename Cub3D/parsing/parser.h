/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelansa <yoelansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 00:56:16 by yoelansa          #+#    #+#             */
/*   Updated: 2023/12/16 16:22:32 by yoelansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <fcntl.h>
# include "../get_next_line/get_next_line.h"

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
	char	player;
	int		player_x;
	int		player_y;
}	t_parser;

// libft
char	*ft_strrchr(char *s, int c);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strdup(char *src);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, size_t start, size_t end);
size_t	ft_strlen(char *str);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strchr(char *s, int c);
char	**ft_split(char *s, char c);
int		ft_atoi(char *str);
int		ft_isdigit(int c);

//pars_colors.c
int		valid_rgb(char *str);
int		get_colors(t_parser	**data, char *line, int k);
char	**get_rgb(char *line);

// general_utils.c
void	ft_exit_error(char *str);
int		is_space(char c);
int		char_counter(char *str, char c);
void	ft_free(char **str);
int		cl_s(char *str);

// data_checks.c
void	data_initialize(t_parser **data);
int		filename_check_open(char *name, int *fd);
char	*pars_direction_name(char *line);
int		data_ready(t_parser *data);
int		valid_map_content(char *str);

// about_map.c
int		check_wall(char *str);
int		check_borders(t_parser	*data, int i, int j);
int		map_info(t_parser **data, char *line, int fd);
int		get_map_width(char **map, int height);
int		check_player(t_parser *data, int i, int j);

// parser.c
void	map_content(t_parser **data, int file_d, char *buffer);
void	look_for_map(t_parser **data, char *buffer, int file_d);
char	*inside_map(t_parser **data, char *path, char *line, int fd);
int		free_mystr(char *str);
void	parser_brain( t_parser **d, int *fd, char *l, char *path);

#endif