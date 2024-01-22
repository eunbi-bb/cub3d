#include "cub3d.h"

/*
*	Updating the orientation anlge('th') of a player.
*	if the angle becomes negative or over 360(_2PI),
*	it adjusts it by adding or substracting 2PI and 
*	ensuring it stays within the range(360).
*/
void	player_rotate(t_data *data, double th)
{
	data->player->th += th;
	if (data->player->th < 0)
		data->player->th += _2PI;
	else if (data->player->th > _2PI) //If the angle is bigger than 360
		data->player->th -= _2PI;
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

/*
*	Moving a player position when a key is pressed.
*	nx and ny are storing the next position of player and
*	the values will be checked by 'get_cell_value()'
*	to prevent the player goes inside of a wall.
*	If nx and ny are not in the wall, update player position
*	into nx and ny.
*/
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