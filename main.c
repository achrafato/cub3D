/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:09:20 by aibn-che          #+#    #+#             */
/*   Updated: 2024/05/31 21:45:09 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	add_to_list(char *line, t_mp **head)
{
	t_mp	*new_line;
	t_mp	*last;

	new_line = malloc(sizeof(t_mp));
	if (!new_line)
		return ;
	new_line->line = line;
	new_line->next = NULL;
	if (!(*head))
		*head = new_line;
	else
	{
		last = *head;
		while (last && last->next)
		{
			last = last->next;
		}
		last->next = new_line;
	}
}

/*
	this function meant to read line by line from a file
*/
t_mp	*accumulate_lines(int fd)
{
	t_mp	*head;
	char	*line;

	line = get_next_line(fd);
	head = NULL;
	while (line)
	{
		add_to_list(line, &head);
		line = get_next_line(fd);
	}
	return (head);
}

void	render_map(char **rows)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		ft_error(NULL, 2, 0);
	fill_data(data, rows);
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->img || (mlx_image_to_window(data->mlx_ptr, data->img, 0, 0) < 0))
		ft_error(data, 2, 0);
	mlx_key_hook(data->mlx_ptr, on_keypress, data);
	mlx_loop_hook(data->mlx_ptr, render_loop, data);
	mlx_loop(data->mlx_ptr);
	mlx_terminate(data->mlx_ptr);
}
int	main(int ac, char **av)
{
	int		fd;
	char	*str;
	t_mp	*lines;
	char	**rows;
	t_list  *var;

	int		i;


	i = 0;

	rows = ft_parsing(ac, av, rows, var);
	// lines = accumulate_lines(fd);
	// rows = conver_to_2d_array(lines);
	while (rows && rows[i])
	{
		printf("%s", rows[i]);
		i++;
	}
	render_map(rows);
	return (0);
}

// int	main(void)
// {
// 	int		file;
// 	char	*str;
// 	t_mp	*lines;
// 	char	**rows;
// 	int		i;

// 	i = 0;
// 	file = open("./map2.cub", O_RDONLY);
// 	lines = accumulate_lines(file);
// 	rows = conver_to_2d_array(lines);
// 	while (rows && rows[i])
// 	{
// 		printf("%s", rows[i]);
// 		i++;
// 	}
// 	render_map(rows);
// 	return (0);
// }
