/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:28:24 by aibn-che          #+#    #+#             */
/*   Updated: 2024/06/04 18:53:43 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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


    // img = ft_get_texture(cube, strip_id);
    // img_px = (int32_t *)img->pixels;
    // offset = (float)(img->height / strip_wall_height);
    // xcord = get_xcord(cube, strip_id, img);
    // ycord = (walltop_to_px - (HEIGHT / 2.0) + (strip_wall_height / 2)) * offset;
    // if (ycord < 0)
    //     ycord = 0;
    // while (walltop_to_px < wallbottom_to_px)
    // {
    //     mlx_put_pixel(cube->img, strip_id, walltop_to_px, \
    //         ft_reverse_color(img_px[((int)ycord * img->width) + (int)xcord]));
    //     ycord += offset;
    //     walltop_to_px++;
    // }

void	build_walls(t_data *data, float ray_angle, t_rays *rays, int i)
{
	t_wall	wall;

	mlx_texture_t	*img;
	int32_t			*img_px;
	float			offset;
	float			xcord;
	float			ycord;

	wall.ds = closest_wall_intersection(data, ray_angle, rays);
	wall.perp_distance = wall.ds * cos(ray_angle - data->pl->rt_angle);
	wall.distance_proj_plane = ((float)WIDTH / 2.0) / tan(FOV / 2);
	wall.projected_wall_height = (CUB_SIZE / wall.perp_distance)
		* wall.distance_proj_plane;
	wall.wall_strip_height = (int)wall.projected_wall_height;
	wall.wall_top_pixel = (HEIGHT / 2) - (wall.wall_strip_height / 2);


	//////////////////////////////////////////////////
	img = ft_get_texture(data, rays);
	img_px = (int32_t *)img->pixels;
	offset = (float)((float)img->height / (float)wall.wall_strip_height);
	xcord = get_xcord(rays, img);
	if (wall.wall_top_pixel < 0)
		wall.wall_top_pixel = 0;
	ycord = ((float)wall.wall_top_pixel - (HEIGHT / 2.0) + ((float)wall.wall_strip_height / 2)) * offset;
	if (ycord < 0)
		ycord = 0;

	//////////////////////////////////////////////////


	wall.wall_bottom_pixel = (HEIGHT / 2) + (wall.wall_strip_height / 2);
	if (wall.wall_bottom_pixel > HEIGHT)
		wall.wall_bottom_pixel = HEIGHT;
	while (wall.wall_top_pixel < wall.wall_bottom_pixel)
	{
		mlx_put_pixel(data->img, i, wall.wall_top_pixel, \
		ft_reverse_color(img_px[((int)ycord * img->width) + (int)xcord]));
		ycord += offset;
		(wall.wall_top_pixel)++;
	}
	data->wall = wall;
}

void	render_3d_view(t_data *data)
{
	int				i;
	t_rays			rays;
	float			ray_angle;

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
