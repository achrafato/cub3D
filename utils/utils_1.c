/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:35:20 by aibn-che          #+#    #+#             */
/*   Updated: 2024/05/30 11:51:16 by aibn-che         ###   ########.fr       */
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
	char	*err;

	if (data)
	{
		if (data->arr)
			free_to_d_arr(data->arr);
		if (data->pl)
			free(data->pl);
		free(data);
	}
	if (a == 1)
		printf("%s\n", mlx_strerror(mlx_errno));
	if (a == 2)
	{
		if (c)
			exit(EXIT_SUCCESS);
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
	max = str_len(rows[0]);
	while (rows && rows[i])
	{
		if (str_len(rows[i]) > max)
			max = str_len(rows[i]);
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
