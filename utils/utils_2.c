/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:40:48 by aibn-che          #+#    #+#             */
/*   Updated: 2024/06/04 10:53:22 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	stack_len(t_mp *lines)
{
	int	i;

	i = 0;
	while (lines)
	{
		i++;
		lines = lines->next;
	}
	return (i);
}

int	rgba(unsigned int r, unsigned int g, unsigned b, unsigned a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	len_of_current_row(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		i++;
	}
	return (i);
}

void	amend_cordinations(int *x, int *y, char **arr)
{
	if (*y < 0)
		*y = 0;
	if (*y >= map_height(arr))
		*y = map_height(arr) - 1;
	if ((len_of_current_row(arr[*y]) <= *x) && *x != 0)
		*x = len_of_current_row(arr[*y]) - 1;
	if (*x < 0)
		*x = 0;
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
