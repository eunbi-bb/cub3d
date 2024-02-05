/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@42.fr>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 12:06:28 by gozturk       #+#    #+#                 */
/*   Updated: 2024/02/01 16:59:10 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	position_to_degree(char p_direction)
{
	if (p_direction == 'N')
		return (deg2rad(90));
	else if (p_direction == 'E')
		return (deg2rad(0));
	else if (p_direction == 'W')
		return (deg2rad(180));
	else
		return (deg2rad(270));
}

static int	close_window(t_data *data)
{
	mlx_close_window(data->mlx);
	puts(mlx_strerror(mlx_errno));
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc != 2)
		err_msg("Wrong number of arguments");
	data.mlx = mlx_init(SX, SY, "cub3d", false);
	if (!data.mlx)
		return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	data.image = mlx_new_image(data.mlx, SX, SY);
	if (!data.image)
		return (close_window(&data));
	if (mlx_image_to_window(data.mlx, data.image, 0, 0) == -1)
		return (close_window(&data));
	parser(argc, argv, &data.file);
	load_textures(&data);
	init_player(&data);
	render(&data);
	mlx_loop_hook(data.mlx, key_press, &data);
	mlx_loop(data.mlx);
	free(data.pl);
	clean_textures(&data);
	mlx_terminate(data.mlx);
	exit(EXIT_SUCCESS);
}
