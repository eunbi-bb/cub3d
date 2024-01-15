#include "cub3d.h"

void	free_arr(char **arr)
{
	int i;

	i = 0;
	if (arr[i])
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
	}
	free(arr);
	arr = NULL;
}

void	free_textures(t_data *data)
{
	free(data->identifier.path_no_texture);
	free(data->identifier.path_so_texture);
	free(data->identifier.path_we_texture);
	free(data->identifier.path_ea_texture);
	mlx_delete_texture(data->identifier.texture_no);
	mlx_delete_texture(data->identifier.texture_so);
	mlx_delete_texture(data->identifier.texture_we);
	mlx_delete_texture(data->identifier.texture_ea);
}