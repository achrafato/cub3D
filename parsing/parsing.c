#include "../cub3D.h"

// int	ft_len_of_map(int fd, char *str)
// {
// 	int		n;
// 	char	*line;
// 	char	*tmp;

// 	n = 0;
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		tmp = ft_remove_nl(line);
// 		free(line);
// 		// printf("%s\n", tmp);
// 		if(tmp && *tmp && !ft_isalpha(*tmp))
// 		{
// 			n++;
// 		}
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	if (open(str, O_RDONLY) == -1)
// 		(write(2, "Error during opening file\n", 26), exit(1)); // free
// 	// printf("here %d\n", n);
// 	return (n);
// }
char	**ft_copy_line(t_pars *pars, char **arr)
{
	int		n;
	char	*line;
	char	*tmp;

	n = 0;
	line = get_next_line(pars->fd);
	while (line)
	{
		tmp = ft_remove_nl(line);
		free(line);
		if (tmp && !*tmp && n > 0)
			(write(2, "Error empty line1\n", 18), exit(1));
		if (tmp && *tmp && !ft_isalpha(*tmp))
		{
			if (!ft_strchr(tmp, '1') && !ft_strchr(tmp, '0'))
				(write(2, "Error empty line\n", 17), exit(1));
			arr[n++] = tmp;
		}
		line = get_next_line(pars->fd);
	}
	arr[n] = NULL;
	return (arr);
}

char **ft_alloc_for_map(t_pars *pars)
{
	char	**rows;

	rows = malloc(sizeof(char *) * (pars->len + 1));
	if (!rows)
		return (NULL);
	printf("%d\n", pars->len);
	rows = ft_copy_line(pars, rows);
	return (rows);
}


char	**ft_parsing(char **rows, t_data *data)
{
	data->pars->fd = open(data->pars->name, O_RDONLY);
	if (data->pars->fd == -1)
		(write(2, "Error during opening file\n", 26), exit(1));
	if (check_extention(data->pars->name, ".cub") != 0)
		(write(2, "Error Invalid extention\n", 26), exit(1));
	ft_check_direction(data);
	rows = ft_alloc_for_map(data->pars);
	if (!rows)
		(write(2, "Error\n", 6), exit(1));
	ft_check_map(rows, data);
	ft_open_img(data);
	return (rows);
}
