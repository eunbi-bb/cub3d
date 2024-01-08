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

#include "MLX42/MLX42_Int.h"

int wall_colors[4] = {COLOR_N, COLOR_S, COLOR_E, COLOR_W};

int map_get_cell( int x, int y )
{
    return (x >= 0 && x < MAPX && y >= 0 && y <= MAPY-1) ? map[x][y] : -1;
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

double cast_single_ray(int x, double px, double py, double th, dir_t *wdir)
{
    double ray = (th + FOVH_2) - (x * ANGLE_PER_PIXEL);

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
/*
*   First while loop: Drawing vertical lines from top to the first pixel of the wall.
*   Second while loop: Drawing vertical lines of the wall.
*   Third while loop: Drawing vertical lines from the end of the wall to bottom.
*/
void    draw_ver_line(int x, int y_start, int y_end, long long color)
{
    int	y;

    y = 0;
    while (y <= y_start)
	{
		mlx_put_pixel(image, x, y, COLOR_BACK);
		y++;
	}
	while (y <= y_end)
	{
		mlx_put_pixel(image, x, y, color);
		y++;
	}
    while (y <= SY -1)
    {
        mlx_put_pixel(image, x, y, COLOR_BACK);
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
void	player_rotate(t_player *pp, double th)
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
		case MLX_KEY_W:
		case MLX_KEY_S:
			*pdx = (key==MLX_KEY_W ? 1 : -1) * amt * cos(th);
            *pdy = (key==MLX_KEY_W ? 1 : -1) * amt * sin(th);
            break;
		case MLX_KEY_A:
        case MLX_KEY_D:
            *pdx = amt * cos(th + (key==MLX_KEY_A ? 1 : -1) * M_PI_2);
            *pdy = amt * sin(th + (key==MLX_KEY_A ? 1 : -1) * M_PI_2);
            break;
		default: /* invalid */
            return -1;
	}
	return (0);
}

int	player_move(t_player *pp, int key, double amt)
{
	double  dx = 0;
	double  dy = 0;
    double  nx;
    double  ny;

	if (get_move_offset(pp->th, key, amt, &dx, &dy) < 0)
	{
		fprintf(stderr, "player_move: invalid key %d\n", key);
		return -1;
	}
	nx = pp->x + dx;
	ny = pp->y + dy;

	printf("nx %d\n", (int)nx);
	printf("ny %d\n", (int)ny);

	if (map_get_cell((int)nx, (int)ny != 0))
	{
		printf(" bump! \n");
		return (-1);
	}
	pp->x = nx;
	pp->y = ny;
	return (0);
}

void key_press(struct mlx_key_data keydata, void *user_data)
{
    keys_t key = keydata.key;
    t_player *pl = (t_player *)user_data;

    if (key == MLX_KEY_ESCAPE)
        exit(EXIT_SUCCESS);
    if (key == MLX_KEY_W || key == MLX_KEY_A || key == MLX_KEY_S || key == MLX_KEY_D)
    {
        if (player_move(pl, key, MOVE_UNIT) == 0)
            render(pl->x, pl->y, pl->th);
    }
    else if (key == MLX_KEY_LEFT || key == MLX_KEY_RIGHT)
    {
        player_rotate(pl, ROT_UNIT * (key == MLX_KEY_LEFT ? 1 : -1));
        render(pl->x, pl->y, pl->th);
    }
}

int main(int ac, char **av)
{
    mlx_t   *mlx;

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
	t_player	pl;
    pl.x = atof(av[1]);
    pl.y = atof(av[2]);
    pl.th = deg2rad(atof(av[3]));

    mlx_key_hook(mlx, key_press, &pl);
    mlx_loop(mlx);
    mlx_terminate(mlx);

    return 0;
}