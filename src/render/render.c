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


/*
*	To retrieve the value of a cell in a map.
*	It checks if the prvided coords (x, y) are within the valind range for the map.
*	It returns the value stored in the correspongin cell of the map[y][x].
*	If the coords are out of bounds, it returns -1.
*/
int get_cell_value(t_data *data, int x, int y)
{
	int	result;
	int	i;

	i = data->file.map.row - 1 - y;
    if (x >= 0 && y >= 0 && y < data->file.map.row \
		&& x < (int)ft_strlen(data->file.map.map_arr[i]))
        result = data->file.map.map_int_arr[y][x];
	else
		result = -1;
	return (result);
}

/*
*	Recieving float number and convert it into the sign (+1 or 0 or -1)
*/
int	sign(double d)
{
	int	result;

	if (is_zero(d))
		result = 0;
	else if (d > 0)
		result = 1;
	else
		result = -1;
	return (result);
}

/*
*	Calculating between two points
*/
double get_distance(double x0, double y0, double x1, double y1)
{
	double dx;
	double dy;

	dx = x0 - x1;
	dy = y0 - y1;
	return (sqrt(dx*dx + dy*dy));
}

void	init_values(t_data *data, double ray)
{
	data->wall.xstep = sign(cos(ray));  /* +1 (right), 0 (no change), -1 (left) */
	data->wall.ystep = sign(sin(ray));  /* +1 (up),    0 (no change), -1 (down) */
	if (data->wall.xstep == 0)
		data->wall.xslope = INFINITY;
	else
		data->wall.xslope = tan(ray);
	if (data->wall.ystep == 0)
		data->wall.yslope = INFINITY;
	else
		data->wall.yslope = 1./tan(ray);
	if (data->wall.xstep > 0)
    	data->wall.nx = floor(data->player->x) + 1;
	else if (data->wall.xstep < 0)
    	data->wall.nx = ceil(data->player->x) - 1;
	else 
    	data->wall.nx = data->player->x;
	if (data->wall.ystep > 0)
    	data->wall.ny = floor(data->player->y) + 1;
	else if (data->wall.ystep < 0)
		data->wall.ny = ceil(data->player->y) - 1;
	else
    	data->wall.ny = data->player->y;
	data->wall.f = INFINITY;
	data->wall.g = INFINITY;
}

int	determine_hitside(t_data *data, double f, double g, int	*hit_side)
{
	int		mapx; 
	int		mapy;
	double	dist_v;
	double	dist_h;

	dist_v = get_distance(data->player->x, data->player->y, data->wall.nx, f);
	dist_h = get_distance(data->player->x, data->player->y, g, data->wall.ny);
	if (dist_v < dist_h)
	{
		mapy = (int)f;
		if (data->wall.xstep == 1)
			mapx = (int)data->wall.nx;
		else
			mapx = (int)(data->wall.nx) - 1;
		*hit_side = VERT;
	}
	else 
	{  /* HORIZ is nearer; go along y-axis */
		mapx = (int)g;
		if (data->wall.ystep == 1)
			mapy = (int)data->wall.ny;
		else
			mapy = (int)(data->wall.ny) - 1;
		*hit_side = HORIZ;
	}
	return (get_cell_value(data, mapx, mapy));	
}

void determine_wall_dir(t_data *data, int hit_side, t_dir *wall_dir, double f, double g)
{
	if (hit_side == VERT)
	{
		if (data->wall.xstep > 0)
			*wall_dir = DIR_E;
		else
			*wall_dir = DIR_W;
		data->wall.wall_x = data->wall.nx;
		data->wall.wall_y = f;
	}
	else
	{
		if (data->wall.ystep > 0)
			*wall_dir = DIR_N;
		else
			*wall_dir = DIR_S;
		data->wall.wall_x = g;
		data->wall.wall_y = data->wall.ny;
	}
}

void	calculate_intersection(t_data *data)
{
	if (data->wall.xstep != 0)
		data->wall.f = data->wall.xslope * (data->wall.nx - data->player->x) + data->player->y;
	if (data->wall.ystep != 0)
		data->wall.g = data->wall.yslope * (data->wall.ny - data->player->y) + data->player->x;
}

/*
*	DDA algorithm. Calculating intersections.
*/
bool get_wall_intersection(t_data *data, double ray, t_dir *wall_dir)
{
	bool	hit;
	int		cell;
	int		hit_side;

	hit = false;
	init_values(data, ray);
	while(!hit)
	{
		calculate_intersection(data);
		cell = determine_hitside(data, data->wall.f, data->wall.g, &hit_side);
		if (cell < 0)
			break ;   /* out of map */
		if (cell == 1)
		{
			determine_wall_dir(data, hit_side, wall_dir, data->wall.f, data->wall.g);
			hit = true;
			break;
		}
		if (hit_side == VERT)
			data->wall.nx += data->wall.xstep;
		else
			data->wall.ny += data->wall.ystep;
	}
	return (hit);
}

/*
*	Casting a single ray. 
*	ANGLE_PER_PIXEL = FOV_H / (SX - 1)
*/
double cast_single_ray(int x, t_data *data, t_dir *wall_dir)
{
	double ray;
	double wall_dist;

	ray = (data->player->th + FOVH_2) - (x * ANGLE_PER_PIXEL);
	if (get_wall_intersection(data, ray, wall_dir) == false)
		return (INFINITY); /* no intersection - maybe bad map? */
	wall_dist = get_distance(data->player->x, data->player->y, data->wall.wall_x, data->wall.wall_y);
	wall_dist *= cos(data->player->th -ray);
	return (wall_dist);
}

int get_wall_height( double dist )
{
	double fov_h;

	fov_h = 2.0 * dist * tan(FOV_V/2.0);
	return ((int)(SY * (WALL_H / fov_h))); /* in pixels */
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

/*********************** TEXTURES *********************/
void    draw_ver_line(t_data *data, int x)
{
	int	y;
	
	y = 0;
	while (y <= data->wall.y_start)
	{
		mlx_put_pixel(data->image, x, y, color_ceiling_floor(data, 'c'));
		y++;
	}
	y = data->wall.y_end;
    while (y <= SY - 1)
    {
        mlx_put_pixel(data->image, x, y, color_ceiling_floor(data, 'f'));
		y++;
	}
}

void	print_texture(t_data *data, int x, int y0, t_dir wall_dir, double light)
{
	mlx_texture_t	*tex;
	int				y;
	int				color;

	tex = texture_dir(data, wall_dir);
	if (wall_dir == DIR_W || wall_dir == DIR_E)
		data->tex.ratio = data->wall.wall_y-floor(data->wall.wall_y);
	else
		data->tex.ratio = data->wall.wall_x-floor(data->wall.wall_x);
	data->tex.x = (int)(data->tex.ratio * tex->width); /* texture column*/
	y = data->wall.y_start;
	while (y <= data->wall.y_end)
	{
		data->tex.y = (int)(((double)(y - y0) * tex->height / data->wall.wall_h)); /* texture row */
		color = fade_color(get_png_rgb(data->tex.x, data->tex.y, tex), light);
		mlx_put_pixel(data->image, x, y, color);
		y++;
	}
}

void    draw_wall(t_data *data, double wdist, int x, t_dir wall_dir)
{
	int		y0; 
	int		y1;
	double light;

	light = get_luminosity(data, wdist);
	data->wall.wall_h = get_wall_height(wdist);
	y0 = (int)((SY - data->wall.wall_h)/ 2.0);
	y1 = y0 + data->wall.wall_h - 1;
	data->wall.y_start = max(0, y0);
	data->wall.y_end = min(SY - 1, y1);
	print_texture(data, x, y0, wall_dir, light);
	draw_ver_line(data, x);
}

void	render(t_data *data)
{
	int		x;
	t_dir	wall_dir;
	double	wall_dist;

	x = 0;
	while (x < SX)
	{
		wall_dist = cast_single_ray(x, data, &wall_dir);
		draw_wall(data, wall_dist, x, wall_dir);
		x++;
	}
}

/***********************************************************************/

//The angle range is from 0 - 360
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
	double angle_offset;

	angle_offset = 0.0;
    if (key == MLX_KEY_W)
        angle_offset = 0.0;
    else if (key == MLX_KEY_S)
        angle_offset = M_PI;
    else if (key == MLX_KEY_A)
        angle_offset = M_PI_2;
    else if (key == MLX_KEY_D)
        angle_offset = -M_PI_2;
    else
        return (-1);
    *pdx = amt * cos(th + angle_offset);
    *pdy = amt * sin(th + angle_offset);
    return (0);
}

int	player_move(t_data *data, int key, double amt)
{
	double	dx;
	double	dy;
	double	nx;
	double	ny;

	dx = 0;
	dy = 0;
	if (get_move_offset(data->player->th, key, amt, &dx, &dy) < 0)
	{
		fprintf(stderr, "player_move: invalid key %d\n", key);
		return (-1);
	}
	nx = data->player->x + dx;
	ny = data->player->y + dy;
	if (get_cell_value(data, (int)nx, (int)ny) != 0)
	{
		printf(" Bump! \n");
		return (-1);
	}
	data->player->x = nx;
	data->player->y = ny;
	return (0);
}

void key_press(struct mlx_key_data keydata, void *game_data)
{
	keys_t key;
	t_data *data;
	int		rotate;

	key = keydata.key;
	data = (t_data *)game_data;
	if (key == MLX_KEY_ESCAPE)
		exit(EXIT_SUCCESS);
	if (key == MLX_KEY_W || key == MLX_KEY_A \
		|| key == MLX_KEY_S || key == MLX_KEY_D)
	{
		if (player_move(data, key, MOVE_UNIT) == 0)
			render(data);
	}
	else if (key == MLX_KEY_LEFT || key == MLX_KEY_RIGHT)
	{
		if (key == MLX_KEY_LEFT)
			rotate = 1;
		else
			rotate = -1;
		player_rotate(data, ROT_UNIT * rotate);
		render(data);
	}
}

/******** Rendering without textures ********/
// int wall_colors[4] = {COLOR_N, COLOR_E, COLOR_W, COLOR_S};

// /*
// *   First while loop: Drawing vertical lines from top to the first pixel of the wall.(Ceiling)
// *   Second while loop: Drawing vertical lines of the wall.
// *   Third while loop: Drawing vertical lines from the end of the wall to bottom.(Floor)
// */
// void    draw_ver_line(t_data *data, int x, int y_start, int y_end, long long color)
// {
// 	int	y;

// 	y = 0;
// 	while (y <= y_start)
// 	{
// 		mlx_put_pixel(data->image, x, y, color_ceiling_floor(data, 'c'));
// 		y++;
// 	}
// 	while (y <= y_end)
// 	{
// 		mlx_put_pixel(data->image, x, y, color);
// 		y++;
// 	}
//     while (y <= SY -1)
//     {
//         mlx_put_pixel(data->image, x, y, color_ceiling_floor(data, 'f'));
// 		y++;
// 	}
// 	// printf("draw ver line\n");
// }

// void    draw_wall(t_data *data, double wdist, int x, long long color)
// {
// 	int wh = get_wall_height(wdist);
// 	int y0 = (int)((SY - wh)/ 2.0);
// 	int y1 = y0 + wh - 1;

// 	int ystart = max(0, y0);
// 	int yend = min(SY - 1, y1);

// 	draw_ver_line(data, x, ystart, yend, color);
// }

// void	render(t_data *data)
// {
// 	load_textures(data);
// 	get_png_rgb(0, 0, data->file.identifier.texture_no);
// 	for( int x=0; x < SX; x++ ) 
// 	{
// 		t_dir	wdir;
// 		double	wdist;
// 		wdist = cast_single_ray(x, data, &wdir);
// 		draw_wall(data, wdist, x, wall_colors[wdir]);
// 	}
// }
