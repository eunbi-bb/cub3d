#include "cub3d.h"

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

void	determine_wall_dir(t_data *data, int hit_side, t_dir *wall_dir, double f, double g)
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
