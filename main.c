/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <salaminty123@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:09:20 by aibn-che          #+#    #+#             */
/*   Updated: 2024/06/11 22:51:18 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	close_window(void	*dt)
{
	t_data	*data;

	data = (t_data *)dt;
	ft_exit(data, "window closed successfully", 0);
}

void	render_map(char **rows, t_data *data)
{
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

void	test_leak(void)
{
	system("leaks cub3D");
}

t_data	*ft_init(t_data *data, char **av)
{
	data = malloc(sizeof(t_data));
	if (!data)
		ft_exit(NULL, "malloc failure (data)", 1);
	// data->pars = NULL; check this function if malloc failed here
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
	data->pl = NULL;
	data->pngs = NULL;
	data->mlx_ptr = NULL;
	data->image = NULL;
	data->arr = NULL;

	return (data);
}

int	main(int ac, char **av)
{
	char	**rows;
	t_data	*data;

	rows = NULL;
	data = NULL;
	// atexit(test_leak);
	if (ac != 2)
		return (1);
	data = ft_init(data, av);
	if (!data)
		return (1);
	rows = ft_parsing(rows, data);
	if (!rows)
		return (1);
	render_map(rows, data);
	return (0);
}
