/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extention.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <salaminty123@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:25:45 by sdemnati          #+#    #+#             */
/*   Updated: 2024/06/13 10:05:04 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
#include <stdio.h>

int	check_extention(char *str1, char *str2)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(str1) - 4;
	while (len < ft_strlen(str1))
	{
		if (str1[len] != str2[i])
			return (str1[len] - str2[i]);
		i++;
		len++;
	}
	return (0);
}

char	*ft_remove_nl(char *str)
{
	int		i;
	char	*line;

	if (!str)
		return (NULL);
	i = 0;
	line = malloc(ft_strlen(str) + 1);
	if (!line)
		return (NULL);
	while (str[i] && str[i] != '\n')
	{
		line [i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	ft_close_open(t_data *data)
{
	close(data->pars->fd);
	data->pars->fd = open(data->pars->name, O_RDONLY);
	if (data->pars->fd == -1)
		ft_exit(data, "Error\nOpen Failed\n", 1);
}
