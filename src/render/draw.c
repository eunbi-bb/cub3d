/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/22 08:56:45 by eucho         #+#    #+#                 */
/*   Updated: 2024/02/01 16:33:39 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
*	Returning a hex code for RGB colors of the ceiling 
*	or floor depending on 'del'.
*/
long long	color_ceiling_floor(t_data *data, char del)
{
	int	colors[3];

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
*	Drawing vertical lines on a screen.
*	The first while loop is drawing a ceiling.
*	The second while loop is drawing a floor.
*/
void	draw_ver_line(t_data *data, int x)
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

/*
*	Drawing walls with texture and a light effect from 'get_luminosity()'.
*	y0 : Starting y postion of the wall slice.
*	y1 : Ending y position of the wall slice.
*	To prevent 'y_start' and 'y_end' from exceeding screen size,
*	compare them to '0' and 'SY' before setting values.
*/
void	draw_wall(t_data *data, double wall_dist, int x, t_dir wall_dir)
{
	int	y0;
	int	y1;

	data->tex.light = get_luminosity(data, wall_dist);
	data->wall.wall_h = get_wall_height(wall_dist);
	y0 = (int)((SY - data->wall.wall_h) / 2.0);
	y1 = y0 + data->wall.wall_h - 1;
	if (0 > y0)
		data->wall.y_start = 0;
	else
		data->wall.y_start = y0;
	if (SY - 1 < y1)
		data->wall.y_end = SY - 1;
	else
		data->wall.y_end = y1;
	print_tex(data, x, y0, wall_dir);
	draw_ver_line(data, x);
}
