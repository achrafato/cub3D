/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:28:26 by aibn-che          #+#    #+#             */
/*   Updated: 2024/06/02 22:08:52 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
	turn_direc -1 if left, 1 if right
	walk_direction  -1 if backward, +1 if forward
*/
t_player	*init_player(void)
{
	t_player	*pl;

	pl = malloc(sizeof(t_player));
	if (!pl)
		return (NULL);
	pl->i = 0;
	pl->j = 0;
	pl->rt_angle = 60 * (M_PI / 180);
	pl->rotation_speed = 5 * (M_PI / 180);
	pl->turn_direc = 0;
	pl->walk_direction = 0;
	pl->move_speed = 20;
	pl->move_step = 0;
	pl->left_right = 0;
	return (pl);
}

void	player_position(char **rows, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (rows[i])
	{
		j = 0;
		while (rows[i][j])
		{
			if (rows[i][j] == 'P')
			{
				*y = i;
				*x = j;
				break ;
			}
			j++;
		}
		i++;
	}
}

void	fill_data(t_data *data, char **arr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->arr = arr;
	data->width = (WIDTH * CUB_SIZE);
	data->height = (HEIGHT * CUB_SIZE);
	data->mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub", true);
	if (!data->mlx_ptr)
		ft_error(data, 1, 0);
	data->pl = init_player();
	if (!data->pl)
		ft_error(data, 2, 0);
	player_position(arr, &j, &i);
	data->pl->i = i * CUB_SIZE;
	data->pl->i += 32;
	data->pl->j = j * CUB_SIZE;
	data->pl->j += 32;
}
