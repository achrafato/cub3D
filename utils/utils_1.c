/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:35:20 by aibn-che          #+#    #+#             */
/*   Updated: 2024/06/11 11:20:11 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	free_to_d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_data(t_data *data)
{
	int		i;

	i = 0;
	if (!data)
		return ;
	if (data->lst)
		ft_lstclear(&data->lst);
	if (data->pars)
		free(data->pars);
	if (data->arr)
		free_to_d_arr(data->arr);
	if (data->pl)
		free(data->pl);
	if (data->pngs)
	{
		while (i < 4)
			mlx_delete_texture(data->pngs[i++]);
		free(data->pngs);
	}
	if (data->mlx_ptr)
	{
		mlx_delete_image(data->mlx_ptr, data->image);
		mlx_terminate(data->mlx_ptr);
	}
	free(data);
}

void	ft_exit(t_data *data, char *msg, int exit_status)
{
	printf("%s\n", msg);
	free_data(data);
	exit(exit_status);
}

int	map_height(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		i++;
	}
	return (i);
}

int	max_width(char **rows)
{
	int	max;
	int	i;

	i = 1;
	max = ft_strlen(rows[0]);
	while (rows && rows[i])
	{
		if (ft_strlen(rows[i]) > max)
			max = ft_strlen(rows[i]);
		i++;
	}
	return (max);
}
