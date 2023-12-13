#ifndef PARSER_H
# define PARSER_H

/*Map Storage infos*/
typedef struct map_data
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		map_height;
	int		map_width;
	int		f[3];
	int		c[3];
	char	**map;
	int		p_x;
	int		p_y;
}			t_data;

/* gobal functions */
void	ft_error(char *msg);
int		skip_spcs(char *str);

/* reading and init functions */
char	*get_next_line(int fd);
void	init_data(t_data **data);

/* map extract functions */
int		calculate_map_width(char **map, int height);
char	*extract_map_content(t_data **data, char *line, int fd, char *path);
int		map_size(t_data **data, char *line, int fd);
int		cpy_map_content(t_data **data, char *line, int fd2);
int		find_and_count_players(t_data *map, int i, int j);
int		count_char(char *str, char c);
int		is_content_valid(char *map);
int		is_filled(t_data *data);
int		is_wall(char *map);

/*Colors extract functions */
int		extract_colors(t_data **data, char *line, int flag, int i);
int		is_valid_num(char *num);

/* memory cleaning functions */
void	free_array(char **strs);

#endif