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
	free(data->file.identifier.path_no);
	free(data->file.identifier.path_so);
	free(data->file.identifier.path_we);
	free(data->file.identifier.path_ea);
	mlx_delete_texture(data->file.identifier.tex_no);
	mlx_delete_texture(data->file.identifier.tex_so);
	mlx_delete_texture(data->file.identifier.tex_we);
	mlx_delete_texture(data->file.identifier.tex_ea);
}