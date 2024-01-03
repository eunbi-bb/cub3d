/*
 *	How to execute
 *	shell $ cc -o ex01 -Wall ex01.c -lm
*	shell $ ./ex01 1.5 3.5 355 
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "cub3d.h"

static mlx_image_t  *image;

#define  SX         400     /* screen width */
#define  SY         250     /* screen height */
#define  FOV        60      /* field of view (in degree) */
#define  FOV_H      deg2rad(FOV)
#define  FOV_V      (FOV_H*(double)SY/(double)SX)
#define  WALL_H     1.0

#define  EPS            (1e-06)
#define  is_zero(d)     (fabs(d) < EPS)
#define  deg2rad(d)     ((d)*M_PI/180.0)    /* degree to radian */
#define  rad2deg(d)     ((d)*180.0/M_PI)    /* radian to degree */
#define  min(a,b)       ((a)<(b)? (a):(b))
#define  max(a,b)       ((a)>(b)? (a):(b))



static const double ANGLE_PER_PIXEL = FOV_H / (SX-1.);
static const double FOVH_2 = FOV_H / 2.0;

enum { VERT, HORIZ };

typedef enum { DIR_N=0, DIR_E, DIR_W, DIR_S } dir_t;

#define  MAPX   6
#define  MAPY   5

#define COLOR_N 0x56BBFD
#define COLOR_S 0x9BF585
#define COLOR_E 0xA585F5
#define COLOR_W 0x85F5D8

int wall_colors[4] = {COLOR_N, COLOR_S, COLOR_E, COLOR_W};


// moving

#define _2PI		6.28318530717958647692  /* 360 degrees */

#define	ROT_UNIT	0.03 /* rad */
#define	MOVE_UNIT	0.1

enum { KEY_OTHER, KEY_W, KEY_A, KEY_S, KEY_D, KEY_LEFT, KEY_RIGHT, KEY_ESC };

typedef struct {
    double x;
    double y;
    double th;
} player_t;

static int map[MAPX][MAPY] = {  /* warning: index order is [x][y] */
    {1,1,1,1,1}, /* [0][*] */
    {1,0,0,0,1}, /* [1][*] */
    {1,0,0,0,1}, /* [2][*] */
    {1,1,0,0,1}, /* and so on... */
    {1,1,0,0,1},
    {1,1,1,1,1}
};

int map_get_cell( int x, int y )
{
    return (x >= 0 && x < MAPX && y >= 0 && y < MAPY) ? map[x][y] : -1;
}

int
sgn( double d )
{
    return is_zero(d) ? 0 : ((d > 0) ? 1 : -1);
}

double l2dist( double x0, double y0, double x1, double y1 )
{
    double dx = x0 - x1;
    double dy = y0 - y1;
    return sqrt(dx*dx + dy*dy);
}

bool get_wall_intersection( double ray, double px, double py, dir_t* wdir, double* wx, double* wy )
{
    int xstep = sgn( cos(ray) );  /* +1 (right), 0 (no change), -1 (left) */
    int ystep = sgn( sin(ray) );  /* +1 (up),    0 (no change), -1 (down) */

    double xslope = (xstep == 0) ? INFINITY : tan(ray);
    double yslope = (ystep == 0) ? INFINITY : 1./tan(ray);

    double nx = (xstep > 0) ? floor(px)+1 : ((xstep < 0) ? ceil(px)-1 : px);
    double ny = (ystep > 0) ? floor(py)+1 : ((ystep < 0) ? ceil(py)-1 : py);

    // printf("\nray=%.2f deg, xstep=%d, ystep=%d, xslope=%.2f, yslope=%.2f, nx=%.2f, ny=%.2f\n",
    //     rad2deg(ray), xstep, ystep, xslope, yslope, nx, ny);

    double f=INFINITY, g=INFINITY;
    bool hit = false;
    int hit_side; /* either VERT or HORIZ */

    while( !hit )
    {
        int mapx, mapy;

        if( xstep != 0 ) f = xslope * (nx-px) + py;
        if( ystep != 0 ) g = yslope * (ny-py) + px;

        /* which is nearer to me - VERT(nx,f) or HORIZ(g,ny)? */
        double dist_v = l2dist(px, py, nx, f);
        double dist_h = l2dist(px, py, g, ny);

        if( dist_v < dist_h ) { /* VERT is nearer; go along x-axis */
            mapx = (xstep == 1) ? (int)(nx) : (int)(nx)-1 ;
            mapy = (int) f;
            hit_side = VERT;
            // printf(" V(%d, %.2f) ->", mapx, f);
        }
        else {  /* HORIZ is nearer; go along y-axis */
            mapx = (int) g;
            mapy = (ystep == 1) ? (int)(ny) : (int)(ny)-1 ;
            hit_side = HORIZ;
            // printf(" H(%.2f, %d) ->", g, mapy);
        }
        int cell = map_get_cell(mapx, mapy);
        if( cell < 0 ) break;   /* out of map */

        if( cell == 1 ) {   /* hit wall? */
            if( hit_side == VERT ) {
                *wdir = (xstep > 0) ? DIR_W : DIR_E;
                *wx = nx;
                *wy = f;
            }
            else { /* HORIZ */
                *wdir = (ystep > 0) ? DIR_S : DIR_N;
                *wx = g;
                *wy = ny;
            }
            hit = true;
            // printf(" hit wall!\n");
            break;
        }

        if( hit_side == VERT ) nx += xstep;
        else ny += ystep;
    }
    /* end of while(!hit) */

    return hit;
}

double cast_single_ray( int x, double px, double py, double th, dir_t *wdir)
{
    double ray = (th + FOVH_2) - (x * ANGLE_PER_PIXEL);

    // dir_t wdir;     /* direction of wall */
    double wx, wy;  /* coord. of wall intersection point */

    if( get_wall_intersection(ray, px, py, wdir, &wx, &wy) == false )
        return INFINITY; /* no intersection - maybe bad map? */

    double wdist = l2dist(px, py, wx, wy);
    wdist *= cos(th -ray);

    return wdist;
}

int
get_wall_height( double dist )
{
    double fov_h = 2.0 * dist * tan(FOV_V/2.0);
    return (int)(SY * (WALL_H / fov_h)); /* in pixels */
}

/*********** MLX ***********/

void    draw_ver_line(int x, int y_start, int y_end, int color)
{
    int	y;

	y = y_start;
	while (y <= y_end)
	{
		mlx_put_pixel(image, x, y, color);
		y++;
	}
}

void    draw_wall(double wdist, int x, long long color)
{
    int wh = get_wall_height(wdist);
    int y0 = (int)((SY - wh)/ 2.0);
    int y1 = y0 + wh - 1;

    int ystart = max(0, y0);
    int yend = min(SY - 1, y1);

    draw_ver_line(x, ystart, yend, color);
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

void	render(double px, double py, double th)
{
	for( int x=0; x<SX; x++ ) 
	{
        dir_t wdir;
        double wdist = cast_single_ray(x, px, py, th, &wdir);
        draw_wall(wdist, x, wall_colors[wdir]);
    }
}

//angle range is from 0 - 360
void	player_rotate(player_t *pp, double th)
{
	pp->th += th;
	if (pp->th < 0)
		pp->th += _2PI;
	else if (pp->th > _2PI) //If the angle is bigger than 360
		pp->th -= _2PI;
}

/*	offset per direction
*	W : (+m cos th, +m sin th)
*	S : (-m cos th, -m sin th)
*	A : (m cos(th + 90), m sin(th + 90))
*	D : (m cos()th - 90),m sin(th - 90))
*/
static int get_move_offset(double th, int key, double amt, double *pdx, double *pdy)
{
	switch(key)
	{
		case KEY_W:
		case KEY_S:
			*pdx = (key==KEY_W ? 1 : -1) * amt * cos(th);
            *pdy = (key==KEY_W ? 1 : -1) * amt * sin(th);
            break;
		case KEY_A:
        case KEY_D:
            *pdx = amt * cos(th + (key==KEY_A ? 1 : -1) * M_PI_2);
            *pdy = amt * sin(th + (key==KEY_A ? 1 : -1) * M_PI_2);
            break;
		default: /* invalid */
            return -1;
	}
	return (0);
}

int	player_move(player_t *pp, int key, double amt)
{
	double dx = 0;
	double dy = 0;

	if (get_move_offset(pp->th, key, amt, &dx, &dy) < 0)
	{
		fprintf(stderr, "player_move: invalid key %d\n", key);
		return -1;
	}
	nx = pp->x + dx;
	ny = pp->y + dy;

	if (map_get_cell((int)nx, (int)ny != 0))
	{
		printf(" bump! \n");
		return (-1);
	}
	pp->x = nx;
	pp->y = ny;
	return (0);
}

int main(int ac, char **av)
{
    mlx_t   *mlx;

    // mlx
    if (!(mlx = mlx_init(SX, SY, "cub3d", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
    if (!(image = mlx_new_image(mlx, SX, SY)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
    if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
    if( ac != 4 ) {
        fprintf(stderr,"usage: %s x y th(deg)\n", av[0]);
        exit(1);
    }
/*******************************/	
	player_t	pl;
    pl.x = atof(av[1]);
    pl.y = atof(av[2]);
    pl.th = deg2rad(atof(av[3]));

	for(;;)
	{
		int	key = get key;
		if (key < 0 ||  key == KEY_ESC)
			break ;
		if (key == KEY_LEFT || key == KEY_RIGHT)
		{
			player_roate(&pl, ROT_UNIT * (key == KEY_LEFT ? 1 : -1));
			render(pl.x, pl.y, pl.th);
		}
		else if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
		{
			if (player_move(&pl, key, MOVE_UNIT) == 0)
				render(pl.x, pl.y, pl.th);
		}
	}

    // mlx_loop_hook(mlx, draw_wall, mlx);
    mlx_loop_hook(mlx, ft_hook, mlx);
    mlx_loop(mlx);
    mlx_terminate(mlx);
    // /* print map */
    // for( int y=MAPY-1; y>=0; y-- ) {
    //     for( int x=0; x<MAPX; x++ ) {
    //         printf("%c ", (map_get_cell(x,y)==1 ? '#':'.'));
    //     }
    //     putchar('\n');
    // }

    // for( int x=0; x<SX; x++ ) {
    //     double wdist = cast_single_ray(x, px, py, th);
    //     printf("** ray %3d : dist %.2f\n", x, wdist);
    // }


    return 0;
}