/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <salaminty123@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:25:48 by sdemnati          #+#    #+#             */
/*   Updated: 2024/06/11 22:27:49 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	ft_check_rgb(char *str)
{
	int	i;

	i = 0;
	if (ft_atoi(str) > 255 || ft_atoi(str) < 0)
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_check_ver(char *str, t_data *data)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			n++;
		i++;
	}
	if (n != 2)
		ft_exit(data, "Error Ver\n", 1);
}

void	ft_parse_rgb(t_data *data, t_list *tmp)
{
	int		i;
	char	**arr;

	i = -1;
	ft_check_ver(tmp->value, data);
	arr = ft_split(tmp->value, ',');
	if (!arr)
		return ;
	while (arr[++i])
		if (ft_check_rgb(arr[i]) || i >= 3)
			(write(2, "Error invalid rgb\n", 18), exit(1));
	if (!ft_strcmp(tmp->type, "C"))
	{
		data->ceil.r = ft_atoi(arr[0]);
		data->ceil.g = ft_atoi(arr[1]);
		data->ceil.b = ft_atoi(arr[2]);
	}
	else if (!ft_strcmp(tmp->type, "F"))
	{
		data->floor.r = ft_atoi(arr[0]);
		data->floor.g = ft_atoi(arr[1]);
		data->floor.b = ft_atoi(arr[2]);
	}
	free_to_d_arr(arr);
}

void	ft_open_img(t_data *data)
{
	t_list	*tmp;

	tmp = data->lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, "F") || !ft_strcmp(tmp->type, "C"))
			ft_parse_rgb(data, tmp);
		else
		{
			if (open(tmp->value, O_RDONLY) == -1)
				(write(2, "Error during opening img\n", 25), exit(1));
		}
		tmp = tmp->next;
	}
}
