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

int wall_colors[4] = {COLOR_N, COLOR_E, COLOR_W, COLOR_S};

/*
*	To retrieve the value of a cell in a map.
*	It checks if the prvided coords (x, y) are within the valind range for the map.
*	It returns the value stored in the correspongin cell of the map[y][x].
*	If the coords are out of bounds, it returns -1.
*/
int map_get_cell(t_data *data, int x, int y)
{
	int	result;

    if (x >= 0 && y < data->file.map.row && x < (int)ft_strlen(data->file.map.map_arr[y]) && y >= 0)
        result = data->file.map.map_int_arr[y][x];
	else
		result = -1;
	return (result);
}

/*
*	Recieving float number and convert it into the sign (+1 or 0 or -1)
*/
int	sgn( double d )
{
	return is_zero(d) ? 0 : ((d > 0) ? 1 : -1);
}

/*
*	Calculating between two points
*/
double get_distance( double x0, double y0, double x1, double y1 )
{
	double dx = x0 - x1;
	double dy = y0 - y1;
	return sqrt(dx*dx + dy*dy);
}

/*
*	DDA algorithm. Calculating intersections.
*/
bool get_wall_intersection(t_data *data, double ray, t_dir* wdir, double* wx, double* wy )
{
	int xstep = sgn( cos(ray) );  /* +1 (right), 0 (no change), -1 (left) */
	int ystep = sgn( sin(ray) );  /* +1 (up),    0 (no change), -1 (down) */

	double xslope = (xstep == 0) ? INFINITY : tan(ray);
	double yslope = (ystep == 0) ? INFINITY : 1./tan(ray);

	// nx and ny are the next intersection coordinates of a ray from (px,py)
	// Intial value is depening on xstep and ystep.
	double nx = (xstep > 0) ? floor(data->player->x)+1 : ((xstep < 0) ? ceil(data->player->x)-1 : data->player->x);
	double ny = (ystep > 0) ? floor(data->player->y)+1 : ((ystep < 0) ? ceil(data->player->y)-1 : data->player->y);

	// printf("\nray=%.2f deg, xstep=%d, ystep=%d, xslope=%.2f, yslope=%.2f, nx=%.2f, ny=%.2f\n",
	//     rad2deg(ray), xstep, ystep, xslope, yslope, nx, ny);

	double f=INFINITY, g=INFINITY;
	bool hit = false;
	int hit_side; /* either VERT or HORIZ */

	while( !hit )
	{
		int mapx, mapy;

		if( xstep != 0 ) f = xslope * (nx - data->player->x) + data->player->y;
		if( ystep != 0 ) g = yslope * (ny - data->player->y) + data->player->x;

		/* which is nearer to me - VERT(nx,f) or HORIZ(g,ny)? */
		double dist_v = get_distance(data->player->x, data->player->y, nx, f);
		double dist_h = get_distance(data->player->x, data->player->y, g, ny);

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
		int cell = map_get_cell(data, mapx, mapy);
		if( cell < 0 ) break;   /* out of map */

		if( cell == 1 ) {   /* hit wall? */
			if( hit_side == VERT ) {
				*wdir = (xstep > 0) ? DIR_E : DIR_E;
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

/*
*	Casting a single ray. 
*	ANGLE_PER_PIXEL = FOV_H / (SX - 1)
*/
double cast_single_ray(int x, t_data *data, t_dir *wdir)
{
	double ray = (data->player->th + FOVH_2) - (x * ANGLE_PER_PIXEL);

	double wx, wy;  /* coord. of wall intersection point */

	if( get_wall_intersection(data, ray, wdir, &wx, &wy) == false )
		return INFINITY; /* no intersection - maybe bad map? */

	double wdist = get_distance(data->player->x, data->player->y, wx, wy);
	wdist *= cos(data->player->th -ray);

	// printf("cast single ray\n");
	return (wdist);
}

int get_wall_height( double dist )
{
	double fov_h = 2.0 * dist * tan(FOV_V/2.0);
	// printf("get_wall_height\n");
	return (int)(SY * (WALL_H / fov_h)); /* in pixels */
}

// void draw_square(t_data *data, int x, int y_end, long long color)
// {
//     int y = 0;
// 	while (x <= 64)
// 	{
// 		while (y <= y_end && y > 0)
// 		{
// 			mlx_put_pixel(data->image, x, y, color);  // Vertical line
// 			y++;
// 		}
// 		x++;
// 	}
// }


void key_press(struct mlx_key_data keydata, void *game_data)
{
	keys_t key = keydata.key;
	t_data *data = (t_data *)game_data;

	if (key == MLX_KEY_ESCAPE)
		exit(EXIT_SUCCESS);
	if (key == MLX_KEY_W || key == MLX_KEY_A || key == MLX_KEY_S || key == MLX_KEY_D)
	{
		if (player_move(data, key, MOVE_UNIT) == 0)
			render(data);
	}
	else if (key == MLX_KEY_LEFT || key == MLX_KEY_RIGHT)
	{
		player_rotate(data, ROT_UNIT * (key == MLX_KEY_LEFT ? 1 : -1));
		render(data);
	}
}
