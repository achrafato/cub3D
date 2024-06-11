/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <salaminty123@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:25:37 by sdemnati          #+#    #+#             */
/*   Updated: 2024/06/11 23:00:41 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	ft_check_duplicate(char *str, t_pars *pars)
{
	if (!str)
		return ;
	if (!ft_strcmp(str, "NO"))
		pars->no++;
	if (!ft_strcmp(str, "SO"))
		pars->so++;
	if (!ft_strcmp(str, "WE"))
		pars->we++;
	if (!ft_strcmp(str, "EA"))
		pars->ea++;
	if (!ft_strcmp(str, "F"))
		pars->f++;
	if (!ft_strcmp(str, "C"))
		pars->c++;
}

void	ft_stor_direction(char *line, t_data *data)
{
	int		i;
	int		j;
	char	*dir;
	t_list	*tmp;
	char	*path;

	i = 0;
	j = 0;
	while (line && line[i] && line[i] == 32)
		i++;
	j = i;
	while (line && line[i] && line[i] != 32)
		i++;
	dir = ft_substr(line, j, i - j);
	ft_check_duplicate(dir, data->pars);
	while (line && line[i] && line[i] == 32)
		i++;
	j = i;
	while (line && line[i])
		i++;
	path = ft_substr(line, j, i - j);
	tmp = ft_lstnew(dir, path);
	if (!tmp)
		ft_exit(data,"Error Malloc Failed\n", 1);
	ft_lstadd_back(&data->lst, tmp);
}

void	ft_check_direction(t_data *data)
{
	char	*line;
	char	*tmp;
	int		i;

	data->lst = NULL;
	data->pars->len = 0;
	line = get_next_line(data->pars->fd);
	while (line)
	{
		i = 0;
		tmp = ft_remove_nl(line);
		while (tmp && tmp[i] && tmp[i] == 32)
			i++;
		if (tmp && tmp[i] && ft_isalpha(tmp[i]))
			ft_stor_direction(tmp, data);
		(free(tmp), free(line));
		line = get_next_line(data->pars->fd);
	}
	if (data->pars->c != 1 || data->pars->f != 1 || data->pars->so != 1
		|| data->pars->we != 1 || data->pars->ea != 1 || data->pars->no != 1)
		ft_exit(data, "Error Not a Direction\n", 1);
	close(data->pars->fd);
	data->pars->fd = open(data->pars->name, O_RDONLY);
	if (data->pars->fd == -1)
		ft_exit(data, "Error Open Failed\n", 1);
}
