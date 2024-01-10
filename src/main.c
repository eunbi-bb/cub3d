#include "cub3d.h"

double	position_to_degree(char p_direction)
{
	if (p_direction == 'N')
		return (deg2rad(90));
	else if (p_direction == 'E')
		return (deg2rad(180));
	else if (p_direction == 'W')
		return (deg2rad(0));
	else
		return (deg2rad(270));
}

int main(int argc, char **argv)
{
	t_data		data;
	mlx_t		*mlx;

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
	if (argc != 2)
		err_msg("Wrong number of arguments");
	parser(argc, argv, &data.file);
		//err_msg("Parser has failded");
    data.player->x = data.file.map.player_pos_x;
    data.player->y = data.file.map.player_pos_y;
    data.player->th = position_to_degree(data.file.map.p_direction);
    mlx_key_hook(mlx, key_press, &data);
    mlx_loop(mlx);
    mlx_terminate(mlx);
}