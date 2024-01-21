#include "cub3d.h"

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

int get_wall_height(double dist)
{
	double fov_h;

	fov_h = 2.0 * dist * tan(FOV_V/2.0);
	return ((int)(SY * (WALL_H / fov_h))); /* in pixels */
}