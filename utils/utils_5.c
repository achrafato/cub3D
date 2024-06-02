/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:28:24 by aibn-che          #+#    #+#             */
/*   Updated: 2024/06/02 22:57:43 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	setting_pl_direction(float ray_angle, t_pl_dr *pl_dr)
{
	int	right;

	right = ray_angle < M_PI / 2 || ray_angle > 270 * (M_PI / 180);
	pl_dr->is_ray_facing_down = ray_angle > 0 && ray_angle < M_PI;
	pl_dr->is_ray_facing_up = !(pl_dr->is_ray_facing_down);
	pl_dr->is_ray_facing_right = right;
	pl_dr->is_ray_facing_left = !(pl_dr->is_ray_facing_right);
}

void	paint_ciel_floor(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < (HEIGHT / 2))
	{
		j = 0;
		while (j < WIDTH)
		{
			mlx_put_pixel(data->img, j, i, rgba(121, 205, 236, 220));
			j++;
		}
		i++;
	}
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			mlx_put_pixel(data->img, j, i, rgba(48, 47, 46, 255));
			j++;
		}
		i++;
	}
}

void	build_walls(t_data *data, float ray_angle, t_rays *rays, int i)
{
	t_wall	wall;

	wall.ds = closest_wall_intersection(data, ray_angle, rays);
	wall.perp_distance = wall.ds * cos(ray_angle - data->pl->rt_angle);
	wall.distance_proj_plane = ((float)WIDTH / 2.0) / tan(FOV / 2);
	wall.projected_wall_height = (CUB_SIZE / wall.perp_distance)
		* wall.distance_proj_plane;
	wall.wall_strip_height = (int)wall.projected_wall_height;
	wall.wall_top_pixel = (HEIGHT / 2) - (wall.wall_strip_height / 2);
	if (wall.wall_top_pixel < 0)
		wall.wall_top_pixel = 0;
	wall.wall_bottom_pixel = (HEIGHT / 2) + (wall.wall_strip_height / 2);
	if (wall.wall_bottom_pixel > HEIGHT)
		wall.wall_bottom_pixel = HEIGHT;
	while (wall.wall_top_pixel < wall.wall_bottom_pixel)
	{
		mlx_put_pixel(data->img, i, wall.wall_top_pixel, \
		rgba(146, 192, 132, 100));
		(wall.wall_top_pixel)++;
	}
}

void	render_3d_view(t_data *data)
{
	int		i;
	t_rays	rays;
	float	ray_angle;

	i = 0;
	paint_ciel_floor(data);
	ray_angle = data->pl->rt_angle - (FOV / 2);
	while (i < WIDTH)
	{
		build_walls(data, ray_angle, &rays, i);
		ray_angle += (FOV / (float)WIDTH);
		i++;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
