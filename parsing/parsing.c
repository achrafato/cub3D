#include "../cub3D.h"
#include <sys/fcntl.h>




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
	if (open(str, O_RDONLY) == -1)
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
void ft_free(char **str)
{
	int i;

	i = 0;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
int ft_check_rgb(char *str)
{
	int	i;

	i = 0;
	if(ft_atoi(str) > 255 || ft_atoi(str) < 0 )
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void ft_open_img(t_data *data)
{
	t_list	*tmp;
	int		i;
	char	**arr;

	tmp = data->lst;
	while(tmp)
	{
		if(!ft_strcmp(tmp->type, "F") || !ft_strcmp(tmp->type, "C") )
		{
			i = -1;
			arr = ft_split(tmp->value, ',');
			if (!arr)
				return ;
			while(arr[++i])
			{
				if (ft_check_rgb(arr[i]) || i >= 3)
					(write(2, "Error invalid rgb\n", 18), exit(1));
			}
			ft_free(arr);
		}
		else
			if (open(tmp->value, O_RDONLY) == -1)
					(write(2, "Error during opening img\n", 25), exit(1));
		tmp = tmp->next;
	}
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
	ft_open_img(data);
	return rows;
}
