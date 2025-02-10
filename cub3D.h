/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemnati <salaminty123@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:15:02 by aibn-che          #+#    #+#             */
/*   Updated: 2024/06/13 10:01:29 by sdemnati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include "/Users/aibn-che/MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# define RED 0xFF0000FF
# define WHITE 0xFFFFFFFF
# define BLACK 0x000000FF
# define GREEN 0x00FF00FF
# define BLUE 0x0000FFFF
# define LEFT 263
# define RIGHT 262
# define UP 87
# define DOWN 83
# define R 68
# define L 65
# define EAST 0
# define WEST 1
# define NORTH 2
# define SOUTH 3

# define D_KEY 68
# define A_KEY 65
# define S_KEY 83
# define W_KEY 87

# define TWO_PI 6.2831853072
# define CUB_SIZE 64
# define MINIMAPSCALE 0.2
# define WIDTH 1920
# define HEIGHT 1080
# define NUM_RAYS WIDTH

typedef struct s_list
{
	char			*type;
	char			*value;
	struct s_list	*next;
}	t_list;

typedef struct s_pars
{
	int		len;
	int		len_line;
	int		no;
	int		so;
	int		ea;
	int		we;
	int		f;
	int		c;
	int		fd;
	int		flag;
	char	*name;
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
	float	horz_hit_distance;
	int		found_horz_wall_hit;
}	t_hr_data;

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
	float	vert_hit_distance;
	int		found_vert_wall_hit;
}	t_vr_data;

typedef struct player
{
	float		i;
	float		j;
	int			turn_direc; // right || left
	float		rotation_speed;
	float		rt_angle;
	int			walk_direction;
	int			move_speed;
	int			move_step;
	int			left_right;
	int			fb_x;
	int			fb_y;
	int			fb_n_x;
	int			fb_n_y;
	int			lr_x;
	int			lr_y;
	int			lf_n_x;
	int			lf_n_y;
	int			player;
}		t_player;

typedef struct wall_info
{
	int		wall_strip_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	float	perp_distance;
	float	distance_proj_plane;
	float	projected_wall_height;
	int		ds;
}		t_wall;

typedef struct texture_infos
{
	mlx_texture_t	*img;
	float			xcord;
	float			ycord;
	float			offset;
	int32_t			*img_px;
}		t_txt_inf;

typedef struct floor_ciel_color
{
	int	r;
	int	g;
	int	b;
}	t_fcc;

typedef struct s_data
{
	float			fov;
	mlx_t			*mlx_ptr;
	void			*win_ptr;
	void			*image;
	char			**arr;
	int				width;
	int				height;
	mlx_image_t		*img;
	mlx_texture_t	**pngs;
	t_player		*pl;
	t_pars			*pars;
	t_wall			wall;
	t_list			*lst;
	t_txt_inf		*txt;
	t_fcc			floor;
	t_fcc			ceil;
}		t_data;

typedef struct Colors
{
	unsigned int	a;
	unsigned int	r;
	unsigned int	b;
	unsigned int	g;
}	t_rgba;

typedef struct Ray
{
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	int		was_hit_vertical;
	int		was_hit_horizontal;
	int		is_ray_facing_up;
	int		is_ray_facing_down;
	int		is_ray_facing_left;
	int		is_ray_facing_right;
	int		wall_hit_content;
}		t_rays;

typedef struct player_direction
{
	int	is_ray_facing_down;
	int	is_ray_facing_up;
	int	is_ray_facing_right;
	int	is_ray_facing_left;
}		t_pl_dr;

// Utils/utils_1.c
void			free_to_d_arr(char **arr);
void			ft_exit(t_data *data, char *msg, int exit_status);
int				map_height(char **arr);
int				max_width(char **rows);

// Utils/utils_2.c
void			set_intersection_distance(t_vr_data *vr, t_hr_data *hr, \
				t_rays *rays);
void			setting_pl_direction(float ray_angle, t_pl_dr *pl_dr);
int				rgba(unsigned int r, unsigned int g, unsigned b, unsigned a);
void			amend_cordinations(int *x, int *y, char **arr);
float			distance_between_points(float x1, float y1, float x2, float y2);

// Utils/utils_3.c
float			normalize_angle(float angle);
void			on_keypress(mlx_key_data_t keydata, void *data);
void			render_loop(void *dt);

// Utils/utils_4.c
float			closest_wall_intersection(t_data *data, float ray_angle, \
				t_rays *rays);

// Utils/utils_5.c
void			paint_ciel_floor(t_data *data);
void			render_3d_view(t_data *data);

// Utils/utils_6.c
mlx_texture_t	*ft_get_texture(t_data *data, t_rays *rays);
float			get_xcord(t_rays *rays, mlx_texture_t *img);
int32_t			ft_reverse_color(int32_t colors);

// Utils/utils_7.c
void			player_position(char **rows, int *x, int *y, t_player *pl);

// init_mlx.c
void			fill_data(t_data *data, char **arr);

//-----------------------get_next_line---------------------
char			*get_next_line(int fd);
int				encounter_space(char *str);
char			*str_join(char **s1, char *s2);
void			handle_nl(char **container, char *buffer, char **keeper);
//-----------------------libft---------------------
char			*ft_substr(const char *str, unsigned int start, size_t len);
char			**ft_split(const char *str, char sep);
void			ft_lstadd_back(t_list **lst, t_list *new1);
t_list			*ft_lstnew(char *dir, char *path);
int				ft_isalpha(int c);
int				ft_strlen(const char *s);
int				ft_atoi(const char *str, t_data *data);
int				ft_isdigit(int c);
int				ft_strcmp(char *s1, char *s2);
void			ft_lstclear(t_list **lst);
//-----------------------parsing---------------------
char			**ft_parsing(char **rows, t_data *data);
void			ft_open_img(t_data *data);
char			*ft_remove_nl(char *str);
int				check_extention(char *str1, char *str2);
void			ft_check_direction(t_data *data);
void			ft_check_map(char **arr, t_data *data);
void			ft_close_open(t_data *data);

#endif
