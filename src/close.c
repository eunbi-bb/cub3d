#include "lib/mlx42/mlx.h"
#include "cub3d.h"

int	esc_hook(int keycode, t_data *vars)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int	close_window(t_data *win)
{
	mlx_destroy_window(win->mlx, win->win);
	exit(0);
	return (0);
}