#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include <stdio.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"

#define  MAPX   24
#define  MAPY   24

#define  EPS            (1e-06)
#define  is_zero(d)     (fabs(d) < EPS)
#define  deg2rad(d)     ((d)*M_PI/180.0)    /* degree to radian */
#define  rad2deg(d)     ((d)*180.0/M_PI)    /* radian to degree */
#define  min(a,b)       ((a)<(b)? (a):(b))
#define  max(a,b)       ((a)>(b)? (a):(b))

# define SX		640
# define SY		480
# define FOV	60
# define FOV_H	deg2rad(FOV)
# define FOV_V	(FOV_H*(double)SY/(double)SX)
# define WALL_H	1.0

static const double ANGLE_PER_PIXEL = FOV_H / (SX-1.);
static const double FOVH_2 = FOV_H / 2.0;

# define ERR_INPUT "Error\nInvalid input : "
# define ERR_MALLOC "Error\nMalloc failed"

typedef struct s_game
{
	void	*mlx;
	void	*win;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	moveSpeed;
	double	rotSpeed;
}	t_game;

typedef enum
{
	DIR_N = 0,
	DIR_E,
	DIR_W,
	DIR_S
}	dir_t;

/*** error.c ***/
int		err_msg(char *str);
void	perror_exit(char *str);

#endif
