/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:40:48 by aibn-che          #+#    #+#             */
/*   Updated: 2024/06/12 13:56:15 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/*
	Down : ray > 0 && ray < 180
	Right : ray < 90 || ray > 270
*/
void	setting_pl_direction(float ray_angle, t_pl_dr *pl_dr)
{
	int	right;

	pl_dr->is_ray_facing_down = ray_angle > 0 && ray_angle < M_PI;
	pl_dr->is_ray_facing_up = !(pl_dr->is_ray_facing_down);
	right = ray_angle < M_PI / 2 || ray_angle > 270 * (M_PI / 180);
	pl_dr->is_ray_facing_right = right;
	pl_dr->is_ray_facing_left = !(pl_dr->is_ray_facing_right);
}

void	set_intersection_distance(t_vr_data *vr, t_hr_data *hr, t_rays *rays)
{
	if (vr)
	{
		rays->distance = vr->vert_hit_distance;
		rays->was_hit_vertical = 1;
		rays->was_hit_horizontal = 0;
		rays->wall_hit_x = vr->wallhit_x_v;
		rays->wall_hit_y = vr->wallhit_y_v;
	}
	else
	{
		rays->distance = hr->horz_hit_distance;
		rays->was_hit_horizontal = 1;
		rays->was_hit_vertical = 0;
		rays->wall_hit_x = hr->wallhit_x_h;
		rays->wall_hit_y = hr->wallhit_y_h;
	}
}

int	rgba(unsigned int r, unsigned int g, unsigned b, unsigned a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	amend_cordinations(int *x, int *y, char **arr)
{
	if (*y < 0)
		*y = 0;
	if (*y >= map_height(arr))
		*y = map_height(arr) - 1;
	if ((ft_strlen(arr[*y]) <= *x) && *x != 0)
		*x = ft_strlen(arr[*y]) - 1;
	if (*x < 0)
		*x = 0;
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
