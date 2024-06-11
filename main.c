/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:09:20 by aibn-che          #+#    #+#             */
/*   Updated: 2024/06/11 11:18:56 by aibn-che         ###   ########.fr       */
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

void	close_window(void	*dt)
{
	t_data	*data;

	data = (t_data *)dt;
	ft_exit(data, "window closed successfully", 0);
}

void	render_map(char **rows, t_data *data)
{
	// t_data	*data;

	// data = malloc(sizeof(t_data));
	// if (!data)
	// 	ft_exit(NULL, 2, 0);
	fill_data(data, rows);
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->img || (mlx_image_to_window(data->mlx_ptr, data->img, 0, 0) < 0))
		ft_exit(data, "mlx_new_image failure", 1);
	mlx_key_hook(data->mlx_ptr, on_keypress, data);
	mlx_loop_hook(data->mlx_ptr, render_loop, data);
	mlx_close_hook(data->mlx_ptr, close_window, data);
	mlx_loop(data->mlx_ptr);
	mlx_terminate(data->mlx_ptr);
}

void test_leak()
{
	system("leaks cub");
}

t_data	*ft_init(t_data *data, char **av)
{
	data = malloc(sizeof(t_data));
	if (!data)
		ft_exit(NULL, "malloc failure (data)", 1);
	data->pars = malloc(sizeof(t_pars));
	if (!data->pars)
		ft_exit(data, "malloc failure (pars)", 1);
	data->pars->c = 0;
	data->pars->ea = 0;
	data->pars->so = 0;
	data->pars->no = 0;
	data->pars->we = 0;
	data->pars->f = 0;
	data->pars->name = av[1];
	return (data);
}

int	main(int ac, char **av)
{
	// t_mp	*lines;
	char	**rows = NULL;
	t_data	*data = NULL;
	if (ac != 2)
		return (1);

	// atexit(&test_leak);
	data = ft_init(data, av);
	if (!data)
		return (1);
	rows = ft_parsing(rows, data);
	if (!rows)
		return (1);
	render_map(rows, data);

	return (0);
}
