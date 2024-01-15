#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "cub3d.h"
#include "MLX42/MLX42_Int.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	load_textures(t_data *data)
{
	data->file.identifier.texture_no = mlx_load_png(data->file.identifier.path_no_texture);
	data->file.identifier.texture_so = mlx_load_png(data->file.identifier.path_so_texture);
	data->file.identifier.texture_we = mlx_load_png(data->file.identifier.path_we_texture);
	data->file.identifier.texture_ea = mlx_load_png(data->file.identifier.path_ea_texture);
	if (data->file.identifier.texture_no == NULL || data->file.identifier.texture_so == NULL
		|| data->file.identifier.texture_we == NULL || data->file.identifier.texture_ea == NULL)
	{
		free_textures(data);
		//free_image(data, NULL);
	}
}

//??? get_texture_side(t_dir *step, int *hit_side)
// {
// 	if (*hit_side == VERT && step->DIR_S < 0)
// 		return (); ??
// 	if (*hit_side == VERT && step->DIR_N > 0)
// 		return (); ??
// 	if (*hit_side == HORIZ && step->DIR_W < 0)
// 		return ();
// 	if (*hit_side == HORIZ && step->DIR_E > 0)
// 		return ();
// 	return (0);
// }

// 	DIR_N=0,
// 	DIR_E, 
// 	DIR_W, 
// 	DIR_S 