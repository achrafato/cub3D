/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <salaminty123@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:25:51 by sdemnati          #+#    #+#             */
/*   Updated: 2024/06/13 10:05:20 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	ft_len_of_map(t_data *data)
{
	int		n;
	char	*line;
	char	*tmp;
	int		len;
	int		i;

	n = 0;
	line = get_next_line(data->pars->fd);
	while (line)
	{
		(1) && (i = 0, tmp = ft_remove_nl(line));
		free(line);
		while (tmp && tmp[i] && tmp[i] == 32)
			i++;
		if (tmp && tmp[i] && !ft_isalpha(tmp[i]))
		{
			len = ft_strlen(tmp);
			if (len > data->pars->len_line)
				data->pars->len_line = len;
			n++;
		}
		free(tmp);
		line = get_next_line(data->pars->fd);
	}
	return (ft_close_open(data), n);
}

char	*ft_fill_line(char *line, t_pars *pars)
{
	int		i;
	char	*full_line;

	i = 0;
	full_line = malloc(pars->len_line + 1);
	if (!full_line)
		return (free(line), NULL);
	while (i < ft_strlen(line))
	{
		full_line[i] = line[i];
		i++;
	}
	while (i < pars->len_line)
	{
		full_line[i++] = ' ';
	}
	full_line[i] = '\0';
	free(line);
	return (full_line);
}

char	**ft_copy_line(t_data *data, char **arr)
{
	int		n;
	char	*line;
	char	*tmp;
	int		i;

	n = 0;
	line = get_next_line(data->pars->fd);
	while (line)
	{
		i = 0;
		tmp = ft_remove_nl(line);
		free(line);
		while (tmp && tmp[i] && tmp[i] == 32)
			i++;
		if ((tmp && n > 0) && (!tmp[i] || ft_isalpha(tmp[i])))
			ft_exit(data, "Error\nMap In The Begining", 1);
		if (tmp && tmp[i] && !ft_isalpha(tmp[i]))
			arr[n++] = ft_fill_line(tmp, data->pars);
		else
			free(tmp);
		line = get_next_line(data->pars->fd);
	}
	arr[n] = NULL;
	return (arr);
}

char	**ft_alloc_for_map(t_data *data)
{
	char	**rows;

	data->pars->len = ft_len_of_map(data);
	rows = malloc(sizeof(char *) * (data->pars->len + 1));
	if (!rows)
		return (NULL);
	rows = ft_copy_line(data, rows);
	return (rows);
}

char	**ft_parsing(char **rows, t_data *data)
{
	data->pars->len_line = 0;
	data->pars->fd = open(data->pars->name, O_RDONLY);
	if (data->pars->fd == -1)
		ft_exit(data, "Error\nOpen Failed", 1);
	if (check_extention(data->pars->name, ".cub") != 0)
		ft_exit(data, "Error\nInvalid Extention", 1);
	ft_check_direction(data);
	rows = ft_alloc_for_map(data);
	if (!rows)
		ft_exit(data, "Error\nNull", 1);
	ft_check_map(rows, data);
	ft_open_img(data);
	return (rows);
}
