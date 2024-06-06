#include "../cub3D.h"

void ft_check_duplicate(char *str, t_pars *pars)
{
	if(!ft_strcmp(str, "NO"))
		pars->no++;
	if(!ft_strcmp(str, "SO"))
		pars->so++;
	if(!ft_strcmp(str, "WE"))
		pars->we++;
	if(!ft_strcmp(str, "EA"))
		pars->ea++;
	if(!ft_strcmp(str, "F"))
		pars->f++;
	if(!ft_strcmp(str, "C"))
		pars->c++;
}
void	ft_stor_direction(char *line, t_data *data)
{
	char **arr;
	t_list *tmp;
	tmp = data->lst;

	arr = ft_split(line, ' ');
	if (!arr)
		return ;
	if (arr && arr[2]) //try to add character in the begining
		(write(2, "Error Invalid len\n", 17), exit(1));
	tmp = ft_lstnew(arr);
	if (!tmp)
		return ;
	ft_check_duplicate(tmp->type, data->pars);
	ft_lstadd_back(&data->lst, tmp);
}


void ft_check_direction(char **arr, t_data *data)
{
	char *line;
	char *tmp;
	data->lst = NULL;

	line = get_next_line(data->pars->fd);
	while(line)
	{
		tmp = ft_remove_nl(line);
		free(line);
		if(tmp && *tmp && ft_isalpha(*tmp))
			ft_stor_direction(tmp, data);
		line = get_next_line(data->pars->fd);
	}
	if (data->pars->c != 1 || data->pars->f != 1 || data->pars->so != 1
		|| data->pars->we != 1 || data->pars->ea != 1 || data->pars->no != 1)
			(write(2, "not 21\n", 7), exit(1));
	close(data->pars->fd);
	data->pars->fd = open(data->pars->name, O_RDONLY);
	if(data->pars->fd == -1)
		(write(2, "Error during opening file\n", 26), exit(1));
}
