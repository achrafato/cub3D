/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:15:02 by aibn-che          #+#    #+#             */
/*   Updated: 2024/05/25 17:55:45 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <float.h>
# include <string.h>
# include "/Users/aibn-che/MLX42/include/MLX42/MLX42.h"
// # include <mlx.h>


#define RED 0xFF0000FF
#define WHITE 0xFFFFFFFF
#define BLACK 0x000000FF
#define GREEN 0x00FF00FF
#define BLUE 0x0000FFFF

#define LEFT 263
#define RIGHT 262
#define UP 265
#define DOWN 264


#define D_KEY 68
#define A_KEY 65
#define S_KEY 83
#define W_KEY 87



#define NUM_RAYS 1000
#define CUB_SIZE 64
#define FOV 60 * (M_PI / 180)
#define MINIMAPSCALE 0.2
#define WIDTH 1920
#define HEIGHT 1080
 
 
 

typedef struct cub_map
{
	char			*line;
	struct cub_map	*next;
} t_mp;

typedef struct player
{
	double			i;
	double			j;
	int 		turnDirection; // right || left
	double		rotationSpeed;
	double		rotationAngle;
	int 		walkDirection;
	int			moveSpeed;
	int			moveStep;
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


	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

}			t_data;

typedef struct Ray
{
	float	rayAngle;
	float		wallHitX;
	float		wallHitY;
	float	distance;
	int		wasHitVertical;
	int		isRayFacingUp;
	int		isRayFacingDown;
	int		isRayFacingLeft;
	int		isRayFacingRight;
	int		wallHitContent;
}			t_rays;