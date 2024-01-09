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
# include "MLX42/MLX42_Int.h"

static mlx_image_t  *image;

#define  SX         800     /* screen width */
#define  SY         500    /* screen height */
#define  FOV        60      /* field of view (in degree) */
#define  FOV_H      deg2rad(FOV)
#define  FOV_V      (FOV_H*(double)SY/(double)SX)
#define  WALL_H     1.0

#define _2PI		6.28318530717958647692  /* 360 degrees */
#define	ROT_UNIT	0.03 /* rad */
#define	MOVE_UNIT	0.1

#define  EPS            (1e-06)
#define  is_zero(d)     (fabs(d) < EPS)
#define  deg2rad(d)     ((d)*M_PI/180.0)    /* degree to radian */
#define  rad2deg(d)     ((d)*180.0/M_PI)    /* radian to degree */
#define  min(a,b)       ((a)<(b)? (a):(b))
#define  max(a,b)       ((a)>(b)? (a):(b))

static const double ANGLE_PER_PIXEL = FOV_H / (SX-1.);
static const double FOVH_2 = FOV_H / 2.0;

#define  MAPX   9
#define  MAPY   9

#define COLOR_N     0x00ffafff
#define COLOR_S     0xffffafff
#define COLOR_E     0xA585F5ff
#define COLOR_W     0x00d7d7ff
#define COLOR_BACK  0x000000ff

enum 
{ 
	VERT, 
	HORIZ 
};

typedef enum
{ 
	DIR_N=0,
	DIR_E, 
	DIR_W, 
	DIR_S 
} dir_t;

typedef struct s_player{
    double x;
    double y;
    double th;
} t_player;

typedef	struct s_img
{
	int		w;
	int		h;
	char	*name;
}	t_img;

/*
*		S
*	E		W
*		N
*/
static int map[MAPX][MAPY] = {  /* warning: index order is [x][y] */
    {1,1,1,1,1,1,1,1,1}, /* [0][*] */
    {1,0,0,0,0,0,0,0,1}, /* [1][*] */
    {1,0,0,0,0,0,0,0,1}, /* [2][*] */
    {1,0,0,0,0,0,0,0,1}, /* and so on... */
	{1,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1},
    {1,1,1,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1}
};

/*** error.c ***/
int		err_msg(char *str);
void	perror_exit(char *str);

/*** move.c ***/
void key_press(struct mlx_key_data keydata, void *user_data);

/*** ray_casting.c ***/
double cast_single_ray(int x, double px, double py, double th, dir_t *wdir);

/*** render.c ***/
int 	map_get_cell( int x, int y );
void	render(double px, double py, double th);

#endif
