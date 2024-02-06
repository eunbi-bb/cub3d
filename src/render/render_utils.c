/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/22 15:25:47 by eucho         #+#    #+#                 */
/*   Updated: 2024/02/06 14:50:14 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
*	Converting degrees to radians.
*/
double	deg2rad(double deg)
{
	return ((deg) * M_PI / 180.0);
}

/*
*	Checking if 'd' is effectively zero or not.
*	Returning 1 if the absolute value of 'd' is less than '1e-06',
*	indicating 'd' is close to zero.
*	fabs() : "floating-point absolute value"
*			to calculate the absolute value of floating-point number.
*	'1e-06' is equal to 0.000001.
*/
int	is_zero(double d)
{
	return (fabs(d) < (1e-06));
}

/*
*	Receiving a floating-point number 
*	and converting it into the sign (+1, 0 or -1).
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
*	It checks if the prvided coordinates (x, y) are within 
*	the valid range for the map.
*	It returns the value stored in the corresponding cell at the map[y][x].
*	If the coords are out of bounds, it returns -1.
*/
int	get_cell_value(t_data *data, int x, int y)
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

int	get_wall_height(double dist)
{
	double	fov_h;
	double	fov_v;

	fov_v = (deg2rad(FOV) * (double)SY / (double)SX);
	fov_h = 2.0 * dist * tan(fov_v / 2.0);
	return ((int)(SY * (WALL_H / fov_h)));
}
