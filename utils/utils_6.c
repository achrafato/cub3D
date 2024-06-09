/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:24:45 by aibn-che          #+#    #+#             */
/*   Updated: 2024/06/03 18:43:34 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

mlx_texture_t	*ft_get_texture(t_data *data, t_rays *rays)
{
	if (rays->was_hit_vertical)
	{
		if (rays->ray_angle < 0.5 * M_PI || rays->ray_angle > 1.5 * M_PI)
			return (data->pngs[0]);
		return (data->pngs[1]);
	}
	else
	{
		if (rays->ray_angle > 0 && rays->ray_angle < M_PI)
			return (data->pngs[2]);
		return (data->pngs[3]);
	}
}

float	get_xcord(t_rays *rays, mlx_texture_t *img)
{
	if (rays->was_hit_vertical)
		return (fmodf(rays->wall_hit_y * (img->width / 64.0), img->width));
	return (fmodf(rays->wall_hit_x * (img->width / 64.0), img->width));
}

int32_t ft_reverse_color(int32_t colors)
{
	t_rgba	color;

	color.a = (colors >> 24) & 0xFF;
	color.r = (colors >> 16) & 0xFF;
	color.g = (colors >> 8) & 0xFF;
	color.b = colors & 0xFF;
	return (((uint32_t)color.b << 24) | ((uint32_t)color.g << 16) \
		| ((uint32_t)color.r << 8) | (uint32_t)color.a);
}
