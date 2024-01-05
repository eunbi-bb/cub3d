#include "cub3d.h"

//angle range is from 0 - 360
void	player_rotate(t_player *pp, double th)
{
	pp->th += th;
	if (pp->th < 0)
		pp->th += _2PI;
	else if (pp->th > _2PI) //If the angle is bigger than 360
		pp->th -= _2PI;
}

/*	offset per direction
*	W : (+m cos th, +m sin th)
*	S : (-m cos th, -m sin th)
*	A : (m cos(th + 90), m sin(th + 90))
*	D : (m cos()th - 90),m sin(th - 90))
*/
int get_move_offset(double th, int key, double amt, double *pdx, double *pdy)
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

int	player_move(t_player *pp, int key, double amt)
{
	double  dx = 0;
	double  dy = 0;
    double  nx;
    double  ny;

	if (get_move_offset(pp->th, key, amt, &dx, &dy) < 0)
	{
		fprintf(stderr, "player_move: invalid key %d\n", key);
		return -1;
	}
	nx = pp->x + dx;
	ny = pp->y + dy;

	if (map_get_cell((int)nx, (int)ny != 0))
	{
		printf(" bump! \n");
		return (-1);
	}
	pp->x = nx;
	pp->y = ny;
	return (0);
}

void key_press(struct mlx_key_data keydata, void *user_data)
{
    keys_t key = keydata.key;
    t_player *pl = (t_player *)user_data;

    if (key == MLX_KEY_ESCAPE)
        exit(EXIT_SUCCESS);
    if (key == MLX_KEY_W || key == MLX_KEY_A || key == MLX_KEY_S || key == MLX_KEY_D)
    {
        if (player_move(pl, key, MOVE_UNIT) == 0)
            render(pl->x, pl->y, pl->th);
    }
    else if (key == MLX_KEY_LEFT || key == MLX_KEY_RIGHT)
    {
        printf("key : %d\n", key);
        player_rotate(pl, ROT_UNIT * (key == MLX_KEY_LEFT ? 1 : -1));
        render(pl->x, pl->y, pl->th);
    }
}
