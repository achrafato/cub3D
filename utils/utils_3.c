/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:56:23 by aibn-che          #+#    #+#             */
/*   Updated: 2024/06/02 23:13:33 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

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
	else if (key == R)
		data->pl->left_right = 1;
	else if (key == L)
		data->pl->left_right = -1;
	data->pl->move_step = data->pl->walk_direction * data->pl->move_speed;
	data->pl->fb_x = data->pl->j + cos(data->pl->rt_angle)
		* data->pl->move_step;
	data->pl->fb_y = data->pl->i + sin(data->pl->rt_angle)
		* data->pl->move_step;
	data->pl->fb_n_x = (data->pl->fb_x + 5);
	data->pl->fb_n_y = (data->pl->fb_y + 5);
	data->pl->lr_x = data->pl->j - (sin(data->pl->rt_angle)
			* data->pl->left_right * data->pl->move_speed);
	data->pl->lr_y = data->pl->i + (cos(data->pl->rt_angle)
			* data->pl->left_right * data->pl->move_speed);
	data->pl->lf_n_x = (data->pl->lr_x + 5);
	data->pl->lf_n_y = (data->pl->lr_y + 5);
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

int	hit_wall(char **arr, int x, int y, float ray_angle)
{
	int		yy;
	int		xx;
	t_pl_dr	pl_dr;

	setting_pl_direction(ray_angle, &pl_dr);
	if (pl_dr.is_ray_facing_up)
		y -= 5;
	else if (pl_dr.is_ray_facing_down)
		y += 5;
	if (pl_dr.is_ray_facing_right)
		x += 5;
	else if (pl_dr.is_ray_facing_left)
		x -= 5;
	(1) && (xx = (x / CUB_SIZE), yy = (y / CUB_SIZE));
	if (yy < 0)
		yy = 0;
	else if (map_height(arr) <= yy)
		yy = map_height(arr) - 1;
	if (xx < 0)
		xx = 0;
	else if (ft_strlen(arr[yy]) <= xx)
		xx = ft_strlen(arr[yy]) - 1;
	if (arr[yy][xx] == '1' || arr[yy][xx] == ' ')
		return (1);
	return (0);
}

void	on_keypress(mlx_key_data_t keydata, void *data)
{
	t_data	*dt;

	dt = (t_data *)data;
	init_turn_and_walk_directions(dt, keydata.key);
	if (keydata.key == 256)
		ft_error(dt, 2, 1);
	if (keydata.key == LEFT || keydata.key == RIGHT)
	{
		dt->pl->rt_angle += dt->pl->turn_direc * dt->pl->rotation_speed;
		dt->pl->rt_angle = normalize_angle(dt->pl->rt_angle);
	}
	else if ((keydata.key == UP || keydata.key == DOWN)
		&& !hit_wall(dt->arr, dt->pl->fb_x, dt->pl->fb_y, dt->pl->rt_angle)
		&& !hit_wall(dt->arr, dt->pl->fb_n_x, dt->pl->fb_n_y, dt->pl->rt_angle))
	{
		dt->pl->i = dt->pl->i + sin(dt->pl->rt_angle) * dt->pl->move_step;
		dt->pl->j = dt->pl->j + cos(dt->pl->rt_angle) * dt->pl->move_step;
	}
	else if ((keydata.key == R || keydata.key == L)
		&& !hit_wall(dt->arr, dt->pl->lr_x, dt->pl->lr_y, dt->pl->rt_angle)
		&& !hit_wall(dt->arr, dt->pl->lf_n_x, dt->pl->lf_n_y, dt->pl->rt_angle))
	{
		dt->pl->j = dt->pl->lr_x;
		dt->pl->i = dt->pl->lr_y;
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
