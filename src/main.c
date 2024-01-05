#include "cub3d.h"

int main(int ac, char **av)
{
    mlx_t   *mlx;

    if (!(mlx = mlx_init(SX, SY, "cub3d", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
    if (!(image = mlx_new_image(mlx, SX, SY)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
    if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
    if( ac != 4 ) {
        fprintf(stderr,"usage: %s x y th(deg)\n", av[0]);
        exit(1);
    }

	t_player	pl;
    pl.x = atof(av[1]);
    pl.y = atof(av[2]);
    pl.th = deg2rad(atof(av[3]));

    mlx_key_hook(mlx, key_press, &pl);
    mlx_loop(mlx);
    mlx_terminate(mlx);

    return 0;
}