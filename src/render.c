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

// int map_get_cell( int x, int y )
// {
//     return (x >= 0 && x < MAPX && y >= 0 && y <= MAPY-1) ? map[x][y] : -1;
// }

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
			mapy = (xstep == 1) ? (int)(nx) : (int)(nx)-1 ;
			mapx = (int) f;
			hit_side = VERT;
			// printf(" V(%d, %.2f) ->", mapx, f);
		}
		else {  /* HORIZ is nearer; go along y-axis */
			mapy = (int) g;
			mapx = (ystep == 1) ? (int)(ny) : (int)(ny)-1 ;
			hit_side = HORIZ;
			// printf(" H(%.2f, %d) ->", g, mapy);
		}
		int cell = map_get_cell(data, mapx, mapy);
		if( cell < 0 ) break;   /* out of map */

		if( cell == 1 ) {   /* hit wall? */
			if( hit_side == VERT ) {
				*wdir = (xstep > 0) ? DIR_E : DIR_W;
				*wx = nx;
				*wy = f;
			}
			else { /* HORIZ */
				*wdir = (ystep > 0) ? DIR_N : DIR_S;
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

long long    color_ceiling_floor(t_data *data, char del)
{
    int		colors[3];

    if (del == 'c')
    {
        colors[0] = data->file.identifier.c_r;
        colors[1] = data->file.identifier.c_g;
        colors[2] = data->file.identifier.c_b;
    }
    else
    {
        colors[0] = data->file.identifier.f_r;
        colors[1] = data->file.identifier.f_g;
        colors[2] = data->file.identifier.f_b;
    }
    return (get_rgba(colors[0], colors[1], colors[2], 255));
}

/*
*   First while loop: Drawing vertical lines from top to the first pixel of the wall.(Ceiling)
*   Second while loop: Drawing vertical lines of the wall.
*   Third while loop: Drawing vertical lines from the end of the wall to bottom.(Floor)
*/
void    draw_ver_line(t_data *data, int x, int y_start, int y_end, long long color)
{
	int	y;

	y = 0;
	while (y <= y_start)
	{
		mlx_put_pixel(data->image, x, y, color_ceiling_floor(data, 'c'));
		y++;
	}
	while (y <= y_end)
	{
		mlx_put_pixel(data->image, x, y, color);
		y++;
	}
    while (y <= SY -1)
    {
        mlx_put_pixel(data->image, x, y, color_ceiling_floor(data, 'f'));
		y++;
	}
	// printf("draw ver line\n");
}

// EUNBI's

// void    draw_wall(t_data *data, double wdist, int x, long long color)
// {
// 	int wh = get_wall_height(wdist);
// 	int y0 = (int)((SY - wh)/ 2.0);
// 	int y1 = y0 + wh - 1;

// 	int ystart = max(0, y0);
// 	int yend = min(SY - 1, y1);
// 	draw_ver_line(data, x, ystart, yend, color);
// 	// printf("draw_wall\n");
// }

void    draw_wall(t_data *data, double wdist, int x, long long color)
{
	int wh = get_wall_height(wdist);
	int y0 = (int)((SY - wh)/ 2.0);
	int y1 = y0 + wh - 1;

	int ystart = max(0, y0);
	int yend = min(SY - 1, y1);

	draw_ver_line(data, x, ystart, yend, color);
	// printf("draw_wall\n");
}

void	render(t_data *data)
{
	for( int x=0; x < SX; x++ ) 
	{
		t_dir	wdir;
		double	wdist;
	// 		draw_ceiling(data);
	// draw_floor(data);
		wdist = cast_single_ray(x, data, &wdir);
		draw_wall(data, wdist, x, wall_colors[wdir]);
	}
	// printf("render\n");
}

//angle range is from 0 - 360
void	player_rotate(t_data *data, double th)
{
	data->player->th += th;
	if (data->player->th < 0)
		data->player->th += _2PI;
	else if (data->player->th > _2PI) //If the angle is bigger than 360
		data->player->th -= _2PI;
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

int	player_move(t_data *data, int key, double amt)
{
	double  dx = 0;
	double  dy = 0;
	double  nx;
	double  ny;

	if (get_move_offset(data->player->th, key, amt, &dx, &dy) < 0)
	{
		fprintf(stderr, "player_move: invalid key %d\n", key);
		return -1;
	}
	nx = data->player->x + dx;
	ny = data->player->y + dy;

	// printf("nx %d\n", (int)nx);
	// printf("ny %d\n", (int)ny);

	if (map_get_cell(data, (int)nx, (int)ny) != 0)
	{
		printf(" bump! \n");
		return (-1);
	}
	data->player->x = nx;
	data->player->y = ny;
			// printf("nx : %f\n", nx);
			// printf("ny : %f\n", ny);
			// printf("player->x : %f\n", data->player->x);
			// printf("player->y : %f\n", data->player->y);
	return (0);
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

	// draw_ceiling(data);
	// draw_floor(data);
	//if (keydata.action == MLX_PRESS)
	//{
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
	//}
}


// int main(int ac, char **av)
// {
//     mlx_t   *mlx;

//     if (!(mlx = mlx_init(SX, SY, "cub3d", true)))
// 	{
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
//     if (!(image = mlx_new_image(mlx, SX, SY)))
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
//     if (mlx_image_to_window(mlx, image, 0, 0) == -1)
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
//     if( ac != 4 ) {
//         fprintf(stderr,"usage: %s x y th(deg)\n", av[0]);
//         exit(1);
//     }
// 	t_player	pl;
//     pl.x = atof(av[1]);
//     pl.y = atof(av[2]);
//     pl.th = deg2rad(atof(av[3]));

//     mlx_key_hook(mlx, key_press, &pl);
//     mlx_loop(mlx);
//     mlx_terminate(mlx);

//     return 0;
// }
