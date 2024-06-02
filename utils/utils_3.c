/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:56:23 by aibn-che          #+#    #+#             */
/*   Updated: 2024/06/01 20:32:31 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_turn_and_walk_directions(t_data *data, int key)
{
	if (key == UP)
		data->pl->walk_direction = 1;
	else if (key == DOWN)
		data->pl->walk_direction = -1;
	else if (key == LEFT)
		data->pl->turn_direc = -1;
	else if (key == RIGHT)
		data->pl->turn_direc = 1;
	data->pl->move_step = data->pl->walk_direction * data->pl->move_speed;
}

/*
	- fmod(angle, TWO_PI)` ensures that the angle is kept within the range
		of a full circle, which is \(0\) to \(2\pi\) radians

	- If the angle is negative, shift it to the positive range [0, 2π)
*/
float	normalize_angle(float angle)
{
	angle = fmod(angle, TWO_PI);
	if (angle < 0)
	{
		angle = TWO_PI + angle;
	}
	return (angle);
}

// void	setting_pl_direction(float ray_angle, t_pl_dr *pl_dr)
// {
// 	int	right;

// 	right = ray_angle < M_PI / 2 || ray_angle > 270 * (M_PI / 180);
// 	pl_dr->is_ray_facing_down = ray_angle > 0 && ray_angle < M_PI;
// 	pl_dr->is_ray_facing_up = !(pl_dr->is_ray_facing_down);
// 	pl_dr->is_ray_facing_right = right;
// 	pl_dr->is_ray_facing_left = !(pl_dr->is_ray_facing_right);
// }

int	hit_wall(char **arr, int x, int y, float ray_angle)
{
	int		yy;
	t_pl_dr	*pl_dr;

	pl_dr = malloc(sizeof(t_pl_dr));
	setting_pl_direction(ray_angle, pl_dr);
	if (pl_dr->is_ray_facing_up)
		y -= 5;
	else if (pl_dr->is_ray_facing_down)
		y += 5;
	yy = (y / CUB_SIZE);
	if (yy < 0)
		yy = 0;
	else if (map_height(arr) <= yy)
		yy = map_height(arr) - 1;
	if (arr[yy][(x / (int)(CUB_SIZE))] == '1' || arr[yy][(x / (int)(CUB_SIZE))] == ' ')
		return (1);
	return (0);
}

// ax  = (py / tan) + px
void	on_keypress(mlx_key_data_t keydata, void *data)
{
	int		x1;
	int		y1;
	int		n_x1;
	int		n_y1;
	t_data	*dt;

	printf("key == %d\n", keydata.key);
	dt = (t_data *)data;
	init_turn_and_walk_directions(dt, keydata.key);
	x1 = dt->pl->j + cos(dt->pl->rotation_angle) * dt->pl->move_step;
	y1 = dt->pl->i + sin(dt->pl->rotation_angle) * dt->pl->move_step;
	n_x1 = (x1 + 5);
	n_y1 = (y1 + 5);
	if (keydata.key == 256)
		ft_error(dt, 2, 1);
	if (keydata.key == LEFT || keydata.key == RIGHT)
	{
		dt->pl->rotation_angle += dt->pl->turn_direc * dt->pl->rotation_speed;
		dt->pl->rotation_angle = normalize_angle(dt->pl->rotation_angle);
	}
	else if ((keydata.key == UP || keydata.key == DOWN)
		&& !hit_wall(dt->arr, x1, y1, dt->pl->rotation_angle)
		&& !hit_wall(dt->arr, n_x1, n_y1, dt->pl->rotation_angle))
	{
		dt->pl->j = dt->pl->j + cos(dt->pl->rotation_angle) * dt->pl->move_step;
		dt->pl->i = dt->pl->i + sin(dt->pl->rotation_angle) * dt->pl->move_step;
	}
	else if (keydata.key == R)
	{
		// int a;
		// a = (dt->pl->j / CUB_SIZE) - 1;
		dt->pl->j = (1 - dt->pl->i / tan(dt->pl->rotation_angle)) + dt->pl->j;
		// dt->pl->i -= 5;
	}
}

void	render_loop(void *dt)
{
	t_data	*data;

	data = (t_data *)dt;
	mlx_delete_image(data->mlx_ptr, data->img);
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->img || (mlx_image_to_window(data->mlx_ptr, data->img, 0, 0) < 0))
		ft_error(data, 2, 0);
	render_3d_view(data);
}
