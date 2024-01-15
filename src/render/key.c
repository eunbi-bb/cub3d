#include "cub3d.h"

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
