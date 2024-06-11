/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:28:24 by aibn-che          #+#    #+#             */
/*   Updated: 2024/06/11 16:09:23 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	paint_ciel_floor(t_data *data)
{
	int	i;
	int	j;
	char **f;
	char **c;

	c = data->fc_color.c;
	f = data->fc_color.f;
	i = 0;
	while (i < (HEIGHT / 2))
	{
		j = 0;
		while (j < WIDTH)
		{
			// mlx_put_pixel(data->img, j, i, rgba(1, 205, 236, 255));
			mlx_put_pixel(data->img, j, i, rgba(ft_atoi(c[0]), ft_atoi(c[1]), ft_atoi(c[2]), 255));
			j++;
		}
		i++;
	}
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			// mlx_put_pixel(data->img, j, i, rgba(48, 47, 46, 255));
			mlx_put_pixel(data->img, j, i, rgba(ft_atoi(f[0]), ft_atoi(f[1]), ft_atoi(f[2]), 255));
			j++;
		}
		i++;
	}
}

void	concluding_top_bottom_walldistance(t_wall *wall, t_data *data, \
		t_rays *rays, float ray_angle)
{
	wall->ds = closest_wall_intersection(data, ray_angle, rays);
	wall->perp_distance = wall->ds * cos(ray_angle - data->pl->rt_angle);
	wall->distance_proj_plane = ((float)WIDTH / 2.0) / tan(data->fov / 2);
	wall->projected_wall_height = (CUB_SIZE / wall->perp_distance)
		* wall->distance_proj_plane;
	wall->wall_strip_height = (int)wall->projected_wall_height;
	wall->wall_top_pixel = (HEIGHT / 2) - (wall->wall_strip_height / 2);
	if (wall->wall_top_pixel < 0)
		wall->wall_top_pixel = 0;
	wall->wall_bottom_pixel = (HEIGHT / 2) + (wall->wall_strip_height / 2);
	if (wall->wall_bottom_pixel > HEIGHT)
		wall->wall_bottom_pixel = HEIGHT;
}

void	texture_info(t_data *data, t_rays *rays, t_wall *wall, t_txt_inf *txt)
{
	float	offset;

	txt->img = ft_get_texture(data, rays);
	offset = (float)((float)txt->img->height / (float)wall->wall_strip_height);
	txt->img_px = (int32_t *)txt->img->pixels;
	txt->offset = offset;
	txt->xcord = get_xcord(rays, txt->img);
	txt->ycord = ((float)wall->wall_top_pixel - (HEIGHT / 2.0)
			+ ((float)wall->wall_strip_height / 2)) * txt->offset;
	if (txt->ycord < 0)
		txt->ycord = 0;
}

void	build_walls(t_data *data, float ray_angle, t_rays *rays, int i)
{
	t_wall			wall;
	t_txt_inf		txt;
	int32_t			color;

	data->txt = &txt;
	concluding_top_bottom_walldistance(&wall, data, rays, ray_angle);
	texture_info(data, rays, &wall, &txt);
	while (wall.wall_top_pixel < wall.wall_bottom_pixel)
	{
		color = txt.img_px[((int)txt.ycord * txt.img->width)
			+ (int)txt.xcord];
		color = ft_reverse_color(color);
		mlx_put_pixel(data->img, i, wall.wall_top_pixel, color);
		txt.ycord += txt.offset;
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
	ray_angle = data->pl->rt_angle - (data->fov / 2);
	while (i < WIDTH)
	{
		build_walls(data, ray_angle, &rays, i);
		ray_angle += (data->fov / (float)WIDTH);
		i++;
	}
}
