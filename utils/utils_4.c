/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:18:49 by aibn-che          #+#    #+#             */
/*   Updated: 2024/05/31 16:44:31 by aibn-che         ###   ########.fr       */
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

/*
	calculate the distance between each horizontal point
		* ystep : represent the next Vertical step
		* xstep : represent the next Horizontal step
	
	found_horz_wall_hit : this var indicate whether or not player
						is collided with wall
*/
void	calc_dis_bt_ech_hr_point(t_pl_dr pl_dr, float ray_angle, t_hr_data *hr)
{
	hr->found_horz_wall_hit = 0;
	hr->ystep = CUB_SIZE;
	if (pl_dr.is_ray_facing_up)
		hr->ystep *= -1;
	hr->xstep = CUB_SIZE / tan(ray_angle);
	if (pl_dr.is_ray_facing_left && hr->xstep > 0)
		hr->xstep *= -1;
	if (pl_dr.is_ray_facing_right && hr->xstep < 0)
		hr->xstep *= -1;
}

/*
	px & py : are the cordination of the player

	ax_h : represent the x-coordinate of the first horizontal point
	ay_h : represent the y-coordinate of the first horizontal point
*/
void	measuring_hr_intersection(t_data *data, float ray_angle, \
		t_pl_dr pl_dr, t_hr_data *hr)
{
	(1) && (hr->px = data->pl->j, hr->py = data->pl->i);
	hr->ay_h = floor(hr->py / CUB_SIZE) * CUB_SIZE;
	if (pl_dr.is_ray_facing_down)
		hr->ay_h += CUB_SIZE;
	hr->ax_h = hr->px + (hr->ay_h - hr->py) / tan(ray_angle);
	calc_dis_bt_ech_hr_point(pl_dr, ray_angle, hr);
	while (hr->ax_h >= 0 && hr->ax_h <= data->width
		&& hr->ay_h >= 0 && hr->ay_h <= data->height)
	{
		(1) && (hr->x_to_check = hr->ax_h, hr->y_to_check = hr->ay_h);
		if (pl_dr.is_ray_facing_up)
			hr->y_to_check -= 1;
		hr->y = floor(hr->y_to_check / CUB_SIZE);
		hr->x = floor(hr->x_to_check / CUB_SIZE);
		amend_cordinations(&(hr->x), &(hr->y), data->arr);
		if (data->arr[hr->y][hr->x] == '1' || data->arr[hr->y][hr->x] == ' ')
		{
			hr->found_horz_wall_hit = 1;
			hr->wallhit_x_h = hr->ax_h;
			hr->wallhit_y_h = hr->ay_h;
			break ;
		}
		else
			(1) && (hr->ax_h += hr->xstep, hr->ay_h += hr->ystep);
	}
}

void	calc_dis_bt_ech_vr_point(t_pl_dr pl_dr, float ray_angle, t_vr_data *vr)
{
	vr->found_vert_wall_hit = 0;
	vr->xstep = CUB_SIZE;
	if (pl_dr.is_ray_facing_left)
		vr->xstep *= -1;
	vr->ystep = CUB_SIZE * tan(ray_angle);
	if (pl_dr.is_ray_facing_up && vr->ystep > 0)
		vr->ystep *= -1;
	if (pl_dr.is_ray_facing_down && vr->ystep < 0)
		vr->ystep *= -1;
}

/*
	px & py : are the cordination of the player
	
	ax_v : represent the x-coordinate of the first vertical point
	ay_v : represent the y-coordinate of the first vertical point
*/
void	measuring_vr_intersection(t_data *data, float ray_angle, \
		t_pl_dr pl_dr, t_vr_data *vr)
{
	(1) && (vr->px = data->pl->j, vr->py = data->pl->i);
	vr->ax_v = floor(vr->px / CUB_SIZE) * CUB_SIZE;
	if (pl_dr.is_ray_facing_right)
		vr->ax_v += CUB_SIZE;
	vr->ay_v = vr->py + (vr->ax_v - vr->px) * tan(ray_angle);
	calc_dis_bt_ech_vr_point(pl_dr, ray_angle, vr);
	while (vr->ax_v >= 0 && vr->ax_v <= data->width
		&& vr->ay_v >= 0 && vr->ay_v <= data->height)
	{
		vr->x_to_check = vr->ax_v;
		if (pl_dr.is_ray_facing_left)
			vr->x_to_check = vr->ax_v - 1;
		vr->y_to_check = vr->ay_v;
		vr->y = floor(vr->y_to_check / CUB_SIZE);
		vr->x = floor(vr->x_to_check / CUB_SIZE);
		amend_cordinations(&(vr->x), &(vr->y), data->arr);
		if (data->arr[vr->y][vr->x] == '1' || data->arr[vr->y][vr->x] == ' ')
		{
			vr->found_vert_wall_hit = 1;
			(1) && (vr->wallhit_x_v = vr->ax_v, vr->wallhit_y_v = vr->ay_v);
			break ;
		}
		else
			(1) && (vr->ax_v += vr->xstep, vr->ay_v += vr->ystep);
	}
}

/*
	closest_wall_intersection() the func purpose is to find the nearest
	distance to the wall from the player position based on the current ray_angle
*/
float	closest_wall_intersection(t_data *data, float ray_angle, t_rays *rays)
{
	t_hr_data	hr;
	t_vr_data	vr;
	t_pl_dr		pl_dr;
	float		horz_hit_distance;
	float		vert_hit_distance;

	horz_hit_distance = FLT_MAX;
	vert_hit_distance = FLT_MAX;
	ray_angle = normalize_angle(ray_angle);
	setting_pl_direction(ray_angle, &pl_dr);
	measuring_hr_intersection(data, ray_angle, pl_dr, &hr);
	measuring_vr_intersection(data, ray_angle, pl_dr, &vr);
	if (hr.found_horz_wall_hit)
		horz_hit_distance = distance_between_points(hr.px, hr.py, \
		hr.wallhit_x_h, hr.wallhit_y_h);
	if (vr.found_vert_wall_hit)
		vert_hit_distance = distance_between_points(vr.px, vr.py, \
		vr.wallhit_x_v, vr.wallhit_y_v);
	if (vert_hit_distance < horz_hit_distance)
		rays->distance = vert_hit_distance;
	else
		rays->distance = horz_hit_distance;
	return (rays->distance);
}

void	build_walls(t_data *data, float ray_angle, t_rays *rays, int i)
{
	int		wall_strip_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	float	perp_distance;
	float	distance_proj_plane;
	float	projected_wall_height;
	int		ds;

	ds = closest_wall_intersection(data, ray_angle, rays);
	perp_distance = ds * cos(ray_angle - data->pl->rotation_angle);
	distance_proj_plane = ((float)WIDTH / 2.0) / tan(FOV / 2);
	projected_wall_height = (CUB_SIZE / perp_distance) * distance_proj_plane;
	wall_strip_height = (int)projected_wall_height;
	wall_top_pixel = (HEIGHT / 2) - (wall_strip_height / 2);
	if (wall_top_pixel < 0)
		wall_top_pixel = 0;
	wall_bottom_pixel = (HEIGHT / 2) + (wall_strip_height / 2);
	if (wall_bottom_pixel > HEIGHT)
		wall_bottom_pixel = HEIGHT;
	while (wall_top_pixel < wall_bottom_pixel)
	{
		mlx_put_pixel(data->img, i, wall_top_pixel, \
		rgba(146, 192,132, 100));
		wall_top_pixel++;
	}
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
			mlx_put_pixel(data->img, j, i,rgba(121,205,236, 220));
			j++;
		}
		i++;
	}
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			mlx_put_pixel(data->img, j, i,rgba(48,47,46, 255));
			j++;
		}
		i++;
	}
}

void	render_3d_view(t_data *data)
{
	int		i;
	t_rays	*rays;
	float	ray_angle;

	i = 0;
	
	paint_ciel_floor(data);
	rays = malloc(sizeof(t_rays));
	if (!rays)
		return ;
	ray_angle = data->pl->rotation_angle - (FOV / 2);
	while (i < WIDTH)
	{
		build_walls(data, ray_angle, rays, i);
		ray_angle += (FOV / (float)WIDTH);
		i++;
	}
}
