/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <salaminty123@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:25:30 by sdemnati          #+#    #+#             */
/*   Updated: 2024/06/11 22:27:34 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	ft_check_first_last(char **arr, t_data *data)
{
	int	i;
	int	j;
	int	len;

	len = data->pars->len - 1;
	i = 0;
	j = 0;
	if (!arr || !*arr)
		return ;
	while (arr[i][j++])
		if (arr[i][j] != '1' && arr[i][j] != 32 && arr[i][j] != '\0')
			ft_exit(data, "Error First Line\n", 1);
	j = 0;
	while (arr[len][j++])
		if (arr[len][j] != '1' && arr[len][j] != ' ' && arr[len][j] != '\0')
			ft_exit(data, "Error Last Line\n", 1);
}

int	ft_check_char(char c)
{
	if (c == '\0' || c == ' ')
		return (-1);
	if (c != '1' && c != '0' && c != ' ' && c != '\0' && c != 'W'
		&& c != 'E' && c != 'S' && c != 'N')
		return (1);
	return (0);
}

void	ft_check_around_map(char **arr, int i, t_data *data)
{
	int	j;
	while (arr[++i])
	{
		j = 0;
		while (arr[i][++j])
		{
			if (arr[i][j] == 'N' || arr[i][j] == 'E'
				|| arr[i][j] == 'W' || arr[i][j] == 'S')
				data->pars->flag++;
			if (ft_check_char(arr[i][j]) == 1)
				ft_exit(data, "Error Invalid Charcter 1\n", 1);
			if (arr[i][j] == '0')
			{
				if (ft_check_char(arr[i + 1][j]) < 0)
					ft_exit(data, "Error Empty Space\n", 1);
				if (ft_check_char(arr[i][j + 1]) < 0)
					ft_exit(data, "Error Empty Space\n", 1);
				if (ft_check_char(arr[i][j - 1]) < 0)
					ft_exit(data, "Error Empty Space\n", 1);
				if (ft_check_char(arr[i - 1][j]) < 0)
					ft_exit(data, "Error Empty Space\n", 1);
			}
		}
	}
}

void	ft_check_map(char **arr, t_data *data)
{
	int	i;

	i = 0;
	data->pars->flag = 0;
	if (!arr || !*arr)
		ft_exit(data, "Error Empty Map\n", 1);
	ft_check_first_last(arr, data);
	ft_check_around_map(arr, i, data);
	if (data->pars->flag != 1)
		ft_exit(data, "Error Unvalid Charcter 2\n", 1);
}
