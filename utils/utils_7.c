/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:17:32 by aibn-che          #+#    #+#             */
/*   Updated: 2024/06/11 15:23:53 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	update_player_rotation(t_player *pl, char player)
{
	if (player == 'E')
		pl->rt_angle = 0 * (M_PI / 180);
	else if (player == 'W')
		pl->rt_angle = 180 * (M_PI / 180);
	else if (player == 'N')
		pl->rt_angle = 270 * (M_PI / 180);
	else if (player == 'S')
		pl->rt_angle = 90 * (M_PI / 180);
}

void	player_position(char **rows, int *x, int *y, t_player *pl)
{
	int	i;
	int	j;

	i = 0;
	while (rows[i])
	{
		j = 0;
		while (rows[i][j])
		{
			if (rows[i][j] == 'N' || rows[i][j] == 'W'
				|| rows[i][j] == 'E' || rows[i][j] == 'S')
			{
				*y = i;
				*x = j;
				update_player_rotation(pl, rows[i][j]);
				break ;
			}
			j++;
		}
		i++;
	}
}
