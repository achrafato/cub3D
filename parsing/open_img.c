#include "../cub3D.h"


void	ft_free(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	ft_check_rgb(char *str)
{
	int	i;

	i = 0;
	if (ft_atoi(str) > 255 || ft_atoi(str) < 0 )
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void ft_check_ver(char *str)
{
	int	i;
	int n;

	n = 0;
	i = 0;
	while(str[i])
	{
		if(str[i] == ',')
			n++;
		i++;
	}
	if (n != 2)
		(write(2, "Error ver\n", 10), exit(1));

}

void	ft_open_img(t_data *data)
{
	t_list	*tmp;
	int		i;
	char	**arr;

	tmp = data->lst;
	while (tmp)
	{
		if(!ft_strcmp(tmp->type, "F") || !ft_strcmp(tmp->type, "C") )
		{
			i = -1;
			ft_check_ver(tmp->value);
			arr = ft_split(tmp->value, ',');
			if (!arr)
				return ;
			while (arr[++i])
				if (ft_check_rgb(arr[i]) || i >= 3)
					(write(2, "Error invalid rgb\n", 18), exit(1));
			ft_free(arr);
		}
		else
			if (open(tmp->value, O_RDONLY) == -1)
					(write(2, "Error during opening img\n", 25), exit(1));
		tmp = tmp->next;
	}
}
