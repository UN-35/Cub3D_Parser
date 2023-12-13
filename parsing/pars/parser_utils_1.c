
#include "../../cub3d.h"

/* init the parsing struct */
void	init_data(t_data **data)
{
	if (!data)
		return ;
	(*data)->no = NULL;
	(*data)->so = NULL;
	(*data)->we = NULL;
	(*data)->ea = NULL;
	(*data)->f[0] = -1;
	(*data)->c[0] = -1;
	(*data)->map = NULL;
	(*data)->map_height = 0;
	(*data)->map_width = 0;
}

/* free double pointer array */
void	free_array(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free (strs);
}

/* count how many char in str */
int	count_char(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (*str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}

/* Skip Sapces at the beginnig */
int	skip_spcs(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

/* Display error  */
void	ft_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
		ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}
