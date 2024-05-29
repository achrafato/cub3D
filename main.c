/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:09:20 by aibn-che          #+#    #+#             */
/*   Updated: 2024/05/27 10:49:07 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

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

char	*str_dup(char *str)
{
	int		i;
	char	*new_str;

	new_str = malloc(sizeof(char) * (str_len(str) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

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

int	lines_len(t_mp *lines)
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

char	**conver_to_2d_array(t_mp *lines)
{
	int		i;
	int		len;
	char	**rows;

	i = 0;
	len = lines_len(lines);
	rows = malloc(sizeof(char *) * (len + 1));
	if (!rows)
		return (NULL);
	while ((i < len) && lines)
	{
		rows[i] = lines->line;
		lines = lines->next;
		i++;
	}
	rows[i] = NULL;
	return (rows);
}

int	map_height(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

int	max_width(char **rows)
{
	int	max;
	int	i;

	i = 1;
	max = str_len(rows[0]);
	while (rows && rows[i])
	{
		if (str_len(rows[i]) > max)
			max = str_len(rows[i]);
		i++;
	}
	return (max);
}


void	fill_data(t_data *data, char **arr)
{
	data->arr = arr;
	data->width = (max_width(arr) * CUB_SIZE);
	data->height = (map_height(arr) * CUB_SIZE);
	// data->width = WIDTH; //1920
	// data->height = HEIGHT; //
	data->mlx_ptr = mlx_init(data->width, data->height, "cub", true);
	// if (!data->mlx_ptr)
	// 	(free_to_d_arr(arr), exit(EXIT_FAILURE));
	// data->win_ptr = mlx_new_window();
	// if (!data->win_ptr)
	// 	(free(data->mlx_ptr), free_to_d_arr(arr), exit(EXIT_FAILURE));
}

void	draw_line1(int x0, int y0, int x1, int y1, t_data *data)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		// printf("x0 = %d   ------ y0 = %d\n", x0, y0);
		mlx_put_pixel(data->img, x0, y0, RED);
		if (x0 == x1 && y0 == y1)
			break;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_line2(int x0, int y0, int x1, int y1, t_data *data)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		// printf("x0 = %d   ------ y0 = %d\n", x0, y0);
		mlx_put_pixel(data->img, x0, y0, WHITE);
		if (x0 == x1 && y0 == y1)
			break;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

int	lef_of_current_row(char *str)
{
	int	i;

	while (str && str[i])
	{
		i++;
	}
	return (i);
}

float distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double	normalize_angle(double angle)
{
    // Reduce the angle to within [-2π, 2π)
    angle = fmod(angle, 2.0 * M_PI);
    // angle = remainder(angle, 2 * TWO_PI);
    
    // If the angle is negative, shift it to the positive range [0, 2π)
    if (angle < 0)
    {
        angle = (2.0 * M_PI) + angle;
    }
    
    // Return the normalized angle
    return (angle);
}

void	amend_cordinations(int *x, int *y, char **arr)
{
	if (*y >= map_height(arr))
		*y = map_height(arr) - 1;
	if (lef_of_current_row(arr[*y]) <= *x && *x != 0)
		*x = lef_of_current_row(arr[*y]) - 1;
}

float	horizontal_intersection(t_data *data, float rayAngle, t_rays *rays)
{
	float	Ay_h;
	float	Ax_h;
	float	Ay_v;
	float	Ax_v;
	float	Py;
	float	Px;
	int		isRayFacingDown;
	int		isRayFacingUp;
	int		isRayFacingRight;
	int		isRayFacingLeft;
	float		xstep;
	float		ystep;
    int		foundHorzWallHit = 0;
    int		foundVertWallHit = 0;

	rayAngle = normalize_angle(rayAngle);
	isRayFacingDown = rayAngle > 0.0 && rayAngle < M_PI;
	isRayFacingUp = !isRayFacingDown;
	isRayFacingRight = rayAngle < M_PI / 2.0 || rayAngle > 270.0 * (M_PI / 180);
	isRayFacingLeft = !isRayFacingRight;

	Py = data->pl->i;
	Px = data->pl->j;

	///////////////////////__Horizontal__/////////////////////////
	//////////////////////////////////////////////////////////////
	Ay_h = floor(Py / CUB_SIZE) * CUB_SIZE;
	Ay_h += isRayFacingDown ? CUB_SIZE : 0;
	Ax_h = Px + (Ay_h - Py) / tan(rayAngle);

	ystep = CUB_SIZE;
	ystep *= isRayFacingUp ? -1 : 1;

	xstep = CUB_SIZE / tan(rayAngle);
	xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
	xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;
	
	float	nextHorzTouchX = Ax_h;
	float	nextHorzTouchY = Ay_h;
	// if (isRayFacingUp)
	// 	nextHorzTouchY--;
	float		wallhitX_H;
	float		wallhitY_H;
	float		wallhitX_V;
	float		wallhitY_V;

	int x, y;
	while (nextHorzTouchX >= 0 && nextHorzTouchX <= (float)data->width && nextHorzTouchY >= 0 && nextHorzTouchY <= (float)data->height)
	{

		float xToCheck = nextHorzTouchX;
        float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);
	
		y = floor(yToCheck / CUB_SIZE);
		x = floor(xToCheck / CUB_SIZE);

		amend_cordinations(&x, &y, data->arr);
		if (data->arr[y][x] == '1' || data->arr[y][x] == ' ')
		{
			foundHorzWallHit = 1;
			wallhitX_H = xToCheck;
			wallhitY_H = yToCheck;
			// draw_line1(data->pl->j, data->pl->i, wallhitX_H, wallhitY_H, data);
			break ;
		}
		else
		{
			nextHorzTouchX += xstep;
			nextHorzTouchY += ystep;
		}
	}
	///////////////////////__Vertical__///////////////////////////
	//////////////////////////////////////////////////////////////
	Ax_v = floor(Px / CUB_SIZE) * CUB_SIZE;
	Ax_v += isRayFacingRight ? CUB_SIZE : 0;
	Ay_v = Py + (Ax_v - Px) * tan(rayAngle);
	
	xstep = CUB_SIZE;
	xstep *= isRayFacingLeft ? -1 : 1;
	
	ystep = CUB_SIZE * tan(rayAngle);
	ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
	ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

	nextHorzTouchX = Ax_v;
	nextHorzTouchY = Ay_v;

	while (nextHorzTouchX >= 0 && nextHorzTouchX <= (float)data->width && nextHorzTouchY >= 0 && nextHorzTouchY <= (float)data->height)
	{
		float xToCheck = nextHorzTouchX + (isRayFacingLeft ? -1 : 0);
		float yToCheck = nextHorzTouchY;

		y = floor(yToCheck / CUB_SIZE);
		x = floor(xToCheck / CUB_SIZE);
		
		// if (y > sizeof(data->arr) / sizeof(data->arr[0]))
		// 	y  = sizeof(data->arr) / sizeof(data->arr[0]);
		amend_cordinations(&x, &y, data->arr);
		// printf("x = %d ----- y = %d\n", x, y);
		if (data->arr[y][x] == '1' || data->arr[y][x] == ' ')
		{
			foundVertWallHit = 1;
			wallhitX_V = xToCheck;
			wallhitY_V = yToCheck;
			// draw_line2(data->pl->j, data->pl->i, wallhitX_V, wallhitY_V, data);
			break ;
		}
		else
		{
			nextHorzTouchX += xstep;
			nextHorzTouchY += ystep;
		}
	}
	// FLT_MAX --> It effectively acts as a placeholder for an infinitely large distance,
		// indicating that no horizontal wall hit was found.

	// euclidean distance
	float horzHitDistance = foundHorzWallHit
		? distanceBetweenPoints(Px, Py, wallhitX_H, wallhitY_H)
		: FLT_MAX;
	float vertHitDistance = foundVertWallHit
		? distanceBetweenPoints(Px, Py, wallhitX_V, wallhitY_V)
		: FLT_MAX;

	int i;
	int j;
    if (vertHitDistance < horzHitDistance)
	{
		rays->distance = vertHitDistance;
		rays->wallHitX = wallhitX_V;
		rays->wallHitY = wallhitY_V;
		// if (lef_of_current_row(data->arr[wallhitY_V / CUB_SIZE]) < wallhitX_V / CUB_SIZE)
		// 	wallhitX_V = lef_of_current_row(data->arr[wallhitY_V / CUB_SIZE]);
		// rays->wallHitContent = data->arr[wallhitY_V / CUB_SIZE][wallhitX_V / CUB_SIZE];
		rays->wasHitVertical = 1;
    }
	else
	{
		rays->distance = horzHitDistance;
		rays->wallHitX = wallhitX_H;
		rays->wallHitY = wallhitY_H;
		// if (lef_of_current_row(data->arr[wallhitY_H / CUB_SIZE]) < wallhitX_H / CUB_SIZE)
		// 	wallhitX_H = lef_of_current_row(data->arr[wallhitY_H / CUB_SIZE]);
		// printf("Y =  %d  ---------  X =  %d \n", wallhitY_H, wallhitX_H);
		// rays->wallHitContent = data->arr[wallhitY_H / CUB_SIZE][wallhitX_H / CUB_SIZE];
		rays->wasHitVertical = 0;
	}
	rays->rayAngle = rayAngle;
	rays->isRayFacingDown = isRayFacingDown;
	rays->isRayFacingUp = isRayFacingUp;
	rays->isRayFacingLeft = isRayFacingLeft;
	rays->isRayFacingRight = isRayFacingRight;
	return (rays->distance);
}

void	draw_line(int x0, int y0, int x1, int y1, t_data *data)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		// printf("x0 = %d   ------ y0 = %d\n", x0, y0);
		mlx_put_pixel(data->img, x0, y0, RED);
		if (x0 == x1 && y0 == y1)
			break;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_straight_line(t_data *data, char **rows, int x, int y)
{
	int	adjacent;
	int	opposite;
	int	hypotenuse;
	int x_pixels;
	int y_pixels;
	double angle_rad;

	angle_rad = data->pl->rotationAngle;
	x_pixels = data->pl->j;
	y_pixels = data->pl->i;
	// printf("x_pixels = %d      ------ y_pixels = %d\n", x_pixels, y_pixels);
	hypotenuse = 60;
	adjacent = (cos(angle_rad) * hypotenuse) + x_pixels;
	opposite = (sin(angle_rad) * hypotenuse) + y_pixels;
	// printf("new X = %d      ------ new Y = %d\n", adjacent, opposite);
	draw_line(x_pixels + MINIMAPSCALE, y_pixels + MINIMAPSCALE, adjacent, opposite, data);
}

void	field_of_view(t_data *data)
{
	t_rays rays[data->width];
	int	i;

	i = 0;
	double ray_angle = data->pl->rotationAngle - (FOV / 2);
	int		wall_strip_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	float	perp_distance;
	float	distance_proj_plane;
	float	projected_wall_height;
	int		ds;

	ray_angle = data->pl->rotationAngle - (FOV / 2);
	while (i < data->width)
	{
		ds = horizontal_intersection(data, ray_angle, rays);
		/***************** INSTRUCTION TO DO *****************/
		perp_distance = ds * cos(ray_angle - data->pl->rotationAngle);
		distance_proj_plane = ((float)data->width / 2.0) / tan(FOV / 2);
		projected_wall_height = (CUB_SIZE / perp_distance) * distance_proj_plane;
		wall_strip_height = (int)projected_wall_height;

		wall_top_pixel = (data->height / 2) - (wall_strip_height / 2);
		wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;

		wall_bottom_pixel = (data->height / 2) + (wall_strip_height / 2);
		wall_bottom_pixel = wall_bottom_pixel > data->height ? data->height : wall_bottom_pixel;

		while (wall_top_pixel < wall_bottom_pixel)
		{
			mlx_put_pixel(data->img, i, wall_top_pixel, rgba(120, 120, 16, 255));
			wall_top_pixel++;
		}
		ray_angle += FOV / (float)data->width;
		i++;
	}

}
	// i = 0;
	// while (i < NUM_RAYS)
	// {
	// 	horizontal_intersection(data, ray_angle, i, &rays[i]);
	// 	ray_angle += FOV / NUM_RAYS;
	// 	i++;
	// }

	// i = 0;
	// while (i < NUM_RAYS)
	// {
	// 	draw_line1(data->pl->j * MINIMAPSCALE, data->pl->i * MINIMAPSCALE, rays[i].wallHitX * MINIMAPSCALE, rays[i].wallHitY * MINIMAPSCALE, data);
	// 	i++;
	// }

void	render_pixels(char **rows, t_data *data)
{
	int	i;
	int	j;
	int	k;
	int	h;
	int	color;
	int x_pixels;
	int y_pixels;

	k = 0;
	h = 0;
	i = 0;
	while (rows && rows[i])
	{
		j = 0;
		y_pixels = i * CUB_SIZE * MINIMAPSCALE;
		while (rows && rows[i][j])
		{
			x_pixels = j * CUB_SIZE * MINIMAPSCALE;
			k = 0;
			if (rows[i][j] == '1' || rows[i][j] == ' ')
				color = BLACK;
			else if (rows[i][j] == '0' || rows[i][j] == 'P')
				color = WHITE;
			h = 0;
			while (h < (CUB_SIZE * MINIMAPSCALE))
			{
				k = 0;
				while (k < (CUB_SIZE * MINIMAPSCALE))
				{
					mlx_put_pixel(data->img, x_pixels + h, y_pixels + k, color);
					k++;
				}
				h++;
			}
			j++;
		}
		i++;
	}
	/////////////////////////////////////////////////////
	/////////// Render player using pixels //////////////
	/////////////////////////////////////////////////////
	color = 0xFF0000;
	x_pixels = data->pl->j * MINIMAPSCALE;
	y_pixels = data->pl->i * MINIMAPSCALE;
	h = 0;
	while (h < 5)
	{
		k = 0;
		while (k < 5)
		{
				mlx_put_pixel(data->img, x_pixels + h, y_pixels + k, RED);
			k++;
		}
		h++;
	}
	/////////////////////////////////////////////////////
	/////////// Render line of view /////////////////////
	/////////////////////////////////////////////////////
}

void	player_position(char **rows, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (rows[i])
	{
		j = 0;
		while (rows[i][j])
		{
			if (rows[i][j] == 'P')
			{
				*y = i;
				*x = j;
				break ;
			}
			j++;
		}
		i++;
	}
}

int	close_window()
{
	exit(0);
}

void	render_loop(void *data)
{

	mlx_delete_image(((t_data *)data)->mlx_ptr, ((t_data *)data)->img);
	((t_data *)data)->img = mlx_new_image(((t_data *)data)->mlx_ptr, ((t_data *)data)->width, ((t_data *)data)->height);
	if (!((t_data *)data)->img || (mlx_image_to_window(((t_data *)data)->mlx_ptr, ((t_data *)data)->img, 0, 0) < 0))
		exit(1);
	// draw_straight_line((t_data *)data, ((t_data *)data)->arr, ((t_data *)data)->pl->j, ((t_data *)data)->pl->i);
	field_of_view((t_data *)data);
	render_pixels(((t_data *)data)->arr, data);

}

t_player	*init_player()
{
	t_player	*pl;

	pl = malloc(sizeof(t_player));
	if (!pl)
		return (NULL);
	pl->i = 0;
	pl->j = 0;
	pl->rotationAngle = 60 * (M_PI / 180);
	// pl->rotationAngle = M_PI * (180 / M_PI);

	pl->rotationSpeed = 5 * (M_PI / 180); ///////////////merror
	pl->turnDirection = 0; // -1 if left, 1 if right

	pl->walkDirection = 0; // -1 if back, +1 if front
	pl->moveSpeed = 10;
	pl->moveStep = pl->walkDirection * pl->moveSpeed;
	return (pl);
}

int	hit_wall(char **arr, int x, int y)
{
	if (arr[(y / (int)(CUB_SIZE))][(x / (int)(CUB_SIZE))] == '1')
	{
		printf("____Hit Wall_____\n");
		printf("x = %d  ------ y = %d\n" ,x / CUB_SIZE, y / CUB_SIZE);
		printf("____Hit Wall_____\n");
		return (1);
	}
	return (0);
}

void	init_up_down_vars(t_data *data, int key)
{
	if (key == UP)
		data->pl->walkDirection = 1;
	else if (key == DOWN)
		data->pl->walkDirection = -1;
	else if (key == LEFT)
		data->pl->turnDirection = -1;
	else if (key == RIGHT)
		data->pl->turnDirection = 1;
	data->pl->moveStep = data->pl->walkDirection * data->pl->moveSpeed;
}

void on_keypress(mlx_key_data_t keydata, void* data)
{
	printf("key = %d\n", keydata.key);
	int x1;
	int y1;
	int n_x1;
	int n_y1;
	t_data	*dt;

	dt = (t_data *)data;
	// n_x1 = dt->pl->j + (5 / (CUB_SIZE * MINIMAPSCALE));
	// n_y1 = dt->pl->i + (5 / (CUB_SIZE * MINIMAPSCALE));

	init_up_down_vars(dt, keydata.key);
	x1 = dt->pl->j + cos(dt->pl->rotationAngle) * dt->pl->moveStep;
	y1 = dt->pl->i + sin(dt->pl->rotationAngle) * dt->pl->moveStep;

	n_x1 = (x1 + 5);
	n_y1 = (y1 + 5);

	if (keydata.key == 256)
		exit(0);
	if (keydata.key == LEFT || keydata.key == RIGHT)
	{
		dt->pl->rotationAngle += dt->pl->turnDirection * dt->pl->rotationSpeed;
		dt->pl->rotationAngle = normalize_angle(dt->pl->rotationAngle);
	}
	else if ((keydata.key == UP || keydata.key == DOWN) && !hit_wall(dt->arr, x1, y1) && !hit_wall(dt->arr, n_x1, n_y1))
	{
		dt->pl->j = dt->pl->j + cos(dt->pl->rotationAngle) * dt->pl->moveStep;
		dt->pl->i = dt->pl->i + sin(dt->pl->rotationAngle) * dt->pl->moveStep;
	}
}

void	render_map(char **rows)
{
	int	i;
	int	j;

	i = 0;
	t_data	*data;

	data = malloc(sizeof(t_data));
	fill_data(data, rows);
	data->pl = init_player();
	player_position(rows, &j, &i);
	data->pl->i = i * CUB_SIZE;
	data->pl->j = j * CUB_SIZE;

	((t_data *)data)->img = mlx_new_image(((t_data *)data)->mlx_ptr, WIDTH, HEIGHT);
	if (!((t_data *)data)->img || (mlx_image_to_window(((t_data *)data)->mlx_ptr, ((t_data *)data)->img, 0, 0) < 0))
		exit(1);
	// render_pixels(rows, data);

	// draw_straight_line(data, rows, j, i);
	// field_of_view(data);

	mlx_key_hook(data->mlx_ptr, on_keypress, data);
	mlx_loop_hook(data->mlx_ptr, render_loop, data);

	mlx_loop(data->mlx_ptr);
	mlx_terminate(data->mlx_ptr);
}

int	main(void)
{
	int		file;
	char	*str;
	t_mp	*lines;
	char	**rows;
	int		i;

	i = 0;
	file = open("./map.cub", O_RDONLY);
	lines = accumulate_lines(file);
	rows = conver_to_2d_array(lines);
	while (rows && rows[i])
	{
		printf("%s", rows[i]);
		i++;
	}
	render_map(rows);
	return (0);
}
