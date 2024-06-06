/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:15:02 by aibn-che          #+#    #+#             */
/*   Updated: 2024/06/01 16:26:43 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

// # include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <errno.h>
# include <float.h>
# include "/Users/sdemnati/MLX42/include/MLX42/MLX42.h"

# define RED 0xFF0000FF
# define WHITE 0xFFFFFFFF
# define BLACK 0x000000FF
# define GREEN 0x00FF00FF
# define BLUE 0x0000FFFF

# define LEFT 263
# define RIGHT 262
# define UP 265
# define DOWN 264
# define R 68
# define L 65

# define D_KEY 68
# define A_KEY 65
# define S_KEY 83
# define W_KEY 87

# define PI 3.14159265358979323846264338327950288
# define TWO_PI (2.0 * PI)
# define CUB_SIZE 64
# define FOV (60 * (PI / 180))
# define MINIMAPSCALE 0.2
# define WIDTH 1920
# define HEIGHT 1080
# define NUM_RAYS WIDTH

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct cub_map
{
	char			*line;
	struct cub_map	*next;
}		t_mp;


typedef struct s_list
{

	char *type;
	char *value;
	struct s_list	*next;
}	t_list;



typedef struct s_pars
{

	int len;
	int no;
	int so;
	int ea;
	int we;
	int f;
	int c;
	int fd;
	int Y;
	char *name;
}	t_pars;


typedef struct horizontal_data
{
	int		x;
	int		y;
	float	py;
	float	px;
	float	ay_h;
	float	ax_h;
	float	xstep;
	float	ystep;
	float	x_to_check;
	float	y_to_check;
	float	wallhit_x_h;
	float	wallhit_y_h;
	int		found_horz_wall_hit;
}		t_hr_data;

typedef struct vertical_data
{
	int		x;
	int		y;
	float	py;
	float	px;
	float	ay_v;
	float	ax_v;
	float	xstep;
	float	ystep;
	float	x_to_check;
	float	y_to_check;
	float	wallhit_x_v;
	float	wallhit_y_v;
	int		found_vert_wall_hit;
}		t_vr_data;

typedef struct player
{
	float		i;
	float		j;
	int			turn_direc; // right || left
	float		rotation_speed;
	float		rotation_angle;
	int			walk_direction;
	int			move_speed;
	int			move_step;
}	t_player;

typedef struct s_data
{
	mlx_t		*mlx_ptr;
	void		*win_ptr;
	void		*image;
	char		**arr;
	int			width;
	int			height;
	mlx_image_t	*img;
	t_player	*pl;
	t_pars	*pars;
	t_list *lst;

	// void		*img_ptr;
	// char		*addr;
	// int			bits_per_pixel;
	// int			line_length;
	// int			endian;
}			t_data;

typedef struct Ray
{
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	int		was_hit_vertical;
	int		is_ray_facing_up;
	int		is_ray_facing_down;
	int		is_ray_facing_left;
	int		is_ray_facing_right;
	int		wall_hit_content;
}			t_rays;

typedef struct player_direction
{
	int	is_ray_facing_down;
	int	is_ray_facing_up;
	int	is_ray_facing_right;
	int	is_ray_facing_left;
}			t_pl_dr;

//-----------------------Utils/utils_1.c---------------------

void	free_to_d_arr(char **arr);
void	ft_error(t_data *data, int a, int c);
int		map_height(char **arr);
int		max_width(char **rows);
char	**conver_to_2d_array(t_mp *lines);

//-----------------------Utils/utils_2.c---------------------

int		stack_len(t_mp *lines);
int		rgba(unsigned int r, unsigned int g, unsigned b, unsigned a);
void	amend_cordinations(int *x, int *y, char **arr);
float	distance_between_points(float x1, float y1, float x2, float y2);

//-----------------------Utils/utils_3.c---------------------

void	init_turn_and_walk_directions(t_data *data, int key);
float	normalize_angle(float angle);
void	on_keypress(mlx_key_data_t keydata, void *data);
void	render_loop(void *dt);

//-----------------------Utils/utils_4.c---------------------

void	setting_pl_direction(float ray_angle, t_pl_dr *pl_dr);
void	render_3d_view(t_data *data);
void	render_pixels(char **rows, t_data *data);

//-----------------------init_mlx.c---------------------

void	fill_data(t_data *data, char **arr);

//-----------------------libft---------------------

int	check_extention(char *str1, char *str2);
size_t	ft_strlen(const char *s);
int	ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_remove_nl(char *str);
char	*ft_strchr(const char *s, int chr);
char	*ft_substr(const char *str, unsigned int start, size_t len);
char	*ft_strdup(const char *str);
char	*ft_strtrim(char const *str, char const *set);
char	**ft_split(const char *str, char sep);
void	ft_lstadd_back(t_list **lst, t_list *new1);
t_list	*ft_lstnew(char **arr);
int	ft_isalpha(int c);
int	ft_strcmp(char *s1, char *s2);
int		str_len(char *str);
char	*str_join(char **s1, char *s2);
int		encounter_space(char *str);
char	*substring(char *s, int index);
void	handle_nl(char **container, char *buffer, char **keeper);
void	mingle_data(char **container, char **buffer, char **keeper);
char	*get_next_line(int fd);

int	ft_atoi(const char *str);
int ft_isdigit(int c);
int	ft_strcmp(char *s1, char *s2);


//-----------------------parsing---------------------

int ft_len_of_map(int fd, char *str);
char **ft_alloc_for_map(t_pars *pars, t_list *var);
char **ft_parsing(int ac, char **rows, t_data *data);


//-----------------------open_img---------------------

int ft_check_rgb(char *str);
void ft_free(char **str);
void ft_open_img(t_data *data);

//-----------------------check_extention---------------------

char	*ft_remove_nl(char *str) ;// check to remove it
int	check_extention(char *str1, char *str2);

//-----------------------direction---------------------

void ft_check_duplicate(char *str, t_pars *pars);
void ft_check_direction(char **arr, t_data *data);

//-----------------------check_map---------------------

int	ft_check_char(char c);
void ft_check_first_last(char **arr, t_pars *pars);
void	ft_check_map(char **arr, t_data *data);

#endif

