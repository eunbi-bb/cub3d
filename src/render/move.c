/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/22 15:25:37 by eucho         #+#    #+#                 */
/*   Updated: 2024/02/01 17:33:58 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
*	Updating the orientation anlge('th') of a player.
*	If the angle becomes negative or exceeds 360 (_2PI),
*	it is adjusted by adding or subtracting 2PI
*	to ensure it stays within the range(0 - 360).
*/
void	player_rotate(t_data *data, double th)
{
	data->pl->th += th;
	if (data->pl->th < 0)
		data->pl->th += _2PI;
	else if (data->pl->th > _2PI)
		data->pl->th -= _2PI;
}

/*	
*	Offset per direction when a player moves.
*	W : (+m cos th, +m sin th)
*	S : (-m cos th, -m sin th)
*	A : (m cos(th + 90), m sin(th + 90))
*	D : (m cos()th - 90), m sin(th - 90))
*	M_PI	= pi = (rad)180
*	M_PI_2	= pi/2 = (rad)90
*/
static int	get_move_offset(double th, int key, double *pdx, double *pdy)
{
	double	angle_offset;
	double	amt;

	amt = MOVE_UNIT;
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

/*
*	Moving a player's position when a key is pressed.
*	'nx' and 'ny' store the next position of the player, 
*	and their values will be checked by 'get_cell_value()'
*	to prevent the player from moving inside a wall.
*	If nx and ny are not within a wall, update player's position
*	to 'nx' and 'ny'.
*/
int	player_move_render(t_data *data, int key)
{
	double	dx;
	double	dy;
	double	nx;
	double	ny;

	dx = 0;
	dy = 0;
	if (get_move_offset(data->pl->th, key, &dx, &dy) < 0)
	{
		return (-1);
	}
	nx = data->pl->x + dx;
	ny = data->pl->y + dy;
	if (get_cell_value(data, (int)nx, (int)ny) != 0)
	{
		printf(" Bump! \n");
		return (-1);
	}
	data->pl->x = nx;
	data->pl->y = ny;
	render(data);
	return (0);
}
