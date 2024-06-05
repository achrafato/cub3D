#include "../cub3D.h"




int ft_len_of_map(int fd, char *str)
{
	int n;
	char *line;
	char *tmp;
	n = 0;
	line = get_next_line(fd);
	while(line)
	{
		tmp = ft_remove_nl(line);
		if(tmp && *tmp && !ft_isalpha(*tmp))
			n++;
		line = get_next_line(fd);
	}
	close(fd);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		(write(2, "Error during opening file\n", 26), exit(1)); // free
	return (n);
}

char **ft_alloc_for_map(t_pars *pars, t_list *var)
{
	int		n;
	char	*line;
	char	**rows;
	char	*tmp;
	pars->len  = ft_len_of_map(pars->fd, pars->name);

	n = 0;
	rows = malloc(sizeof(char *) * (pars->len + 1));
	if (!rows)
		return (NULL);
	line = get_next_line(pars->fd);
	while (line)
	{
		tmp = ft_remove_nl(line);
		free(line);
		if(tmp && *tmp && !ft_isalpha(*tmp))
			rows[n++] = tmp;
		line = get_next_line(pars->fd);
	}
	rows[n] = NULL;
	return (rows);
}

char	**ft_parsing(int ac, char **rows, t_data *data)
{
	int	i;

	i = 0;

	data->pars->fd = open(data->pars->name, O_RDONLY);
	if (data->pars->fd == -1)
		(write(2, "Error during opening file\n", 26), exit(1));
	if (check_extention(data->pars->name, ".cub") != 0)
		(write(2, "Error Invalid extention\n", 26), exit(1));
	ft_check_direction(rows, data);
	rows = ft_alloc_for_map(data->pars, data->lst);
	if (!rows)
		(write(2, "Error\n", 6), exit(1));
	ft_check_map(rows, data->pars);
	return rows;
}
