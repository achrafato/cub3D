/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:35:20 by aibn-che          #+#    #+#             */
/*   Updated: 2024/06/03 16:15:12 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	free_to_d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i++]);
	}
	free(arr);
}

// Exit the program as failure.
void	ft_error(t_data *data, int a, int c)
{
	// char	*err;
	int		i;

	i = 0;
	if (data)
	{
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
		mlx_delete_image(data->mlx_ptr, data->image);
		mlx_terminate(data->mlx_ptr);
		free(data);
	}
	if (a == 1)
		printf("%s\n", mlx_strerror(mlx_errno));
	if (a == 2)
	{
		if (c)
			exit(EXIT_FAILURE);
		printf("%s\n", strerror(errno));
	}
	exit(EXIT_FAILURE);
}

int	map_height(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
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

char	**conver_to_2d_array(t_mp *lines)
{
	int		i;
	int		len;
	char	**rows;

	i = 0;
	len = stack_len(lines);
	rows = malloc(sizeof(char *) * (len + 1));
	if (!rows)
		return (NULL);
	while ((i < len) && lines)
	{
		rows[i] = lines->line;
		lines = lines->next;
		i++;
	}
	rows[i] = NULL;
	return (rows);
}
