#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "cub3d.h"
#include "MLX42/MLX42_Int.h"

void	draw_ceiling(t_data *data)
{
	int	y;
	int	x;
	int		colors[3];

	colors[0] = data->identifier.c_r;
	colors[1] = data->identifier.c_g;
	colors[2] = data->identifier.c_b;
	y = SY / 2;
	while (y < SY)
	{
		x = 0;
		while (x < SX)
		{
			mlx_put_pixel(data->image, x, y, get_rgba(colors[0],
					colors[1], colors[2], 255));
			++x;
		}
		++y;
	}
}

void	draw_floor(t_data *data)
{
	int	y;
	int	x;
	int	colors[3];

	colors[0] = data->identifier.f_r;
	colors[1] = data->identifier.f_g;
	colors[2] = data->identifier.f_b;
	y = 0;
	while (y < SY / 2)
	{
		x = 0;
		while (x < SX)
		{
			mlx_put_pixel(data->image, x, y, get_rgba(colors[0],
					colors[1], colors[2], 255));
			++x;
		}
		++y;
	}
}
