/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   luminosity.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/22 15:25:24 by eucho         #+#    #+#                 */
/*   Updated: 2024/01/23 08:57:04 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Light effect */
/*
*	Extracting individual RGB components.
*/
void	decode_rgb(int color, int *r, int *g, int *b)
{
	*r = (color >> 24) & 0xFF;
	*g = (color >> 16) & 0xFF;
	*b = (color >> 8) & 0xFF;
}

/*
*	Combining RGB components into a single integer color representation.
*/
int	encode_rgb(int r, int g, int b, int a)
{
	r = (r & 0xFF) << 24;
	g = (g & 0xFF) << 16;
	b = (b & 0xFF) << 8;
	a = a & 0xFF;
	return (r | g | b | a);
}

/*
*   Adjusting the intensity of the color based on the light
*   and returning the modified rgb color. 
*/
int	fade_color(int color, double light)
{
	int	r;
	int	g;
	int	b;
	int	a;

	if (light < 0)
		light = 0;
	else if (light > 1)
		light = 1;
	decode_rgb(color, &r, &g, &b);
	a = color & 0xFF;
	r = (int)(r * light);
	g = (int)(g * light);
	b = (int)(b * light);
	a = (int)(a * light);
	return (encode_rgb(r, g, b, a));
}

/*
*	Returning a value between 0 - 1 depending on dist.
*	map_xamax() and map_ymax() are getting the value of MAPX and MAPY.
*	static var is in order to reduce duplicated calculation
*	and avoid using of const.
*/
double	get_luminosity(t_data *data, double dist)
{
	static double	l;

	l = -1;
	if (l < 0)
		l = (data->file.map.row + data->file.map.column) / 2.0;
	if (dist > l)
		return (0);
	else
		return (1. - dist / l);
}
