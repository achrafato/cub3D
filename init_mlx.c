/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:28:26 by aibn-che          #+#    #+#             */
/*   Updated: 2024/06/05 11:03:42 by aibn-che         ###   ########.fr       */
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

void	update_player_rotation(t_player *pl, char player)
{
	if (player == 'E')
		pl->rt_angle = 0 * (M_PI / 180);
	else if (player == 'N')
		pl->rt_angle = 90 * (M_PI / 180);
	else if (player == 'S')
		pl->rt_angle = 180 * (M_PI / 180);
	else if (player == 'W')
		pl->rt_angle = 270 * (M_PI / 180);
}

void	player_position(char **rows, int *x, int *y, t_player *pl)
{
	int	i;
	int	j;

	i = 0;
	while (rows[i])
	{
		j = 0;
		while (rows[i][j])
		{
			if (rows[i][j] == 'N' || rows[i][j] == 'W' || rows[i][j] == 'E' || rows[i][j] == 'S')
			{
				*y = i;
				*x = j;
				update_player_rotation(pl, rows[i][j]);
				break ;
			}
			j++;
		}
		i++;
	}
}

mlx_texture_t	**load_pictures(void)
{
	mlx_texture_t	**pngs;
	int				i;
	char			*arr[4];

	pngs = NULL;
	arr[0] = "./textures/image_1.png";
	arr[1] = "./textures/image_2.png";
	arr[2] = "./textures/image_5.png";
	arr[3] = "./textures/image_3.png";
	i = 0;
	pngs = malloc(sizeof(mlx_texture_t *) * 4);
	if (!pngs)
		return (NULL);
	while (i < 4)
	{
		pngs[i] = mlx_load_png(arr[i]);
		i++;
	}
	return (pngs);
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
	player_position(arr, &j, &i, data->pl);
	data->pl->i = i * CUB_SIZE;
	data->pl->i += 32;
	data->pl->j = j * CUB_SIZE;
	data->pl->j += 32;
	data->pngs = load_pictures();
	if (!data->pngs)
		ft_error(data, 2, 1);
}
