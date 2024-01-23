/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_casting.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/22 12:37:03 by eucho         #+#    #+#                 */
/*   Updated: 2024/01/23 09:10:45 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
*	Calculating a Euclidean distance between the two points.
*	sqrt()	: calculate the square root of a given number.
*/
double	get_e_dist(double x0, double y0, double x1, double y1)
{
	double	dx;
	double	dy;

	dx = x0 - x1;
	dy = y0 - y1;
	return (sqrt((dx * dx) + (dy * dy)));
}

/*
*	Deciding a hit_side depending on distance of horizontal or vertical lines.
* 	To find a wall, a shorter distance between dist_v and dist_h 
*	is needed to be chosen and set the map index (mapx and mapy) 
*	from the intersection. 
*	'xstep' and 'ystep' are representing step size in x or y direction.
*	In order to set a correct 'mapx' and 'mapy' index,
*	checking values of 'xstep' and 'ystep'.
*	As the last, check if 'mapx' and 'mapy' index is wall or not
*	by 'get_cell_value()'.
*/
int	determine_hitside(t_data *data, double f, double g, int	*hit_side)
{
	int		mapx;
	int		mapy;

	data->wall.dist_v = get_e_dist(data->pl->x, data->pl->y, data->wall.nx, f);
	data->wall.dist_h = get_e_dist(data->pl->x, data->pl->y, g, data->wall.ny);
	if (data->wall.dist_v < data->wall.dist_h)
	{
		*hit_side = VERT;
		mapy = (int)f;
		if (data->wall.xstep == 1)
			mapx = (int)data->wall.nx;
		else
			mapx = (int)(data->wall.nx) - 1;
	}
	else
	{
		*hit_side = HORIZ;
		mapx = (int)g;
		if (data->wall.ystep == 1)
			mapy = (int)data->wall.ny;
		else
			mapy = (int)(data->wall.ny) - 1;
	}
	return (get_cell_value(data, mapx, mapy));
}

/*
*				(ystep > 0)
*					N
*	(xstep <= 0) W	*  E (xstep > 0)
*					S
*				(ystep <= 0)
*	Deciding a wall direction depending on hit_side.
*	After deciding a wall direction, update 'wall_x' and 'wall_y' values to
*	the next coordination.
*/
void	determine_wall_dir(t_data *data, int hit_side, t_dir *wall_dir)
{
	if (hit_side == VERT)
	{
		if (data->wall.xstep > 0)
			*wall_dir = DIR_E;
		else
			*wall_dir = DIR_W;
		data->wall.wall_x = data->wall.nx;
		data->wall.wall_y = data->wall.f;
	}
	else
	{
		if (data->wall.ystep > 0)
			*wall_dir = DIR_N;
		else
			*wall_dir = DIR_S;
		data->wall.wall_x = data->wall.g;
		data->wall.wall_y = data->wall.ny;
	}
}

/*
*	A linear function and inverse function calculation in order to find
*	a intersection.
*	When it's not verticality(xstep != 0) or horizontality(ystep != 0).
*	f : y = mx + c (slope * (nx - x) + y)
*	g : x = my + c (slope * (ny - y) + x)
*/
void	calculate_intersection(t_data *data)
{
	if (data->wall.xstep != 0)
		data->wall.f = data->wall.xslope * (data->wall.nx - data->pl->x) \
		+ data->pl->y;
	if (data->wall.ystep != 0)
		data->wall.g = data->wall.yslope * (data->wall.ny - data->pl->y) \
		+ data->pl->x;
}

/*
*	DDA algorithm. Calculating intersections.
*	Depending on which intersection is got hit, adding step to nx or ny.
*	Basically, moving the nx or ny toward vertically or horixontally 1 step
*	to the nearest side.
*/
bool	get_intersection(t_data *data, double ray, t_dir *wall_dir)
{
	bool	hit;
	int		cell;
	int		hit_side;

	hit = false;
	init_values(data, ray);
	while (!hit)
	{
		calculate_intersection(data);
		cell = determine_hitside(data, data->wall.f, data->wall.g, &hit_side);
		if (cell < 0)
			break ;
		if (cell == 1)
		{
			determine_wall_dir(data, hit_side, wall_dir);
			hit = true;
			break ;
		}
		if (hit_side == VERT)
			data->wall.nx += data->wall.xstep;
		else
			data->wall.ny += data->wall.ystep;
	}
	return (hit);
}
