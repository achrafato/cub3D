/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:18:49 by aibn-che          #+#    #+#             */
/*   Updated: 2024/06/03 19:14:17 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/*
	calculate the distance between each horizontal point
		* ystep : represent the next Vertical step
		* xstep : represent the next Horizontal step

	was_hit_horizontal : this var indicate whether or not player
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
		printf("y = %d   ---- x = %d  \n", vr->y, vr->x);
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

	horz_hit_distance = MAXFLOAT;
	vert_hit_distance = MAXFLOAT;
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
	{
		rays->distance = vert_hit_distance;
		rays->was_hit_vertical = 1;
		rays->was_hit_horizontal = 0;
		rays->wall_hit_x = vr.wallhit_x_v;
		rays->wall_hit_y = vr.wallhit_y_v;
	}
	else
	{
		rays->distance = horz_hit_distance;
		rays->was_hit_horizontal = 1;
		rays->was_hit_vertical = 0;
		rays->wall_hit_x = hr.wallhit_x_h;
		rays->wall_hit_y = hr.wallhit_y_h;
	}
	rays->ray_angle = ray_angle;
	return (rays->distance);
}
