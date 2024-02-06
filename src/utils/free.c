/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@42.fr>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 12:05:54 by gozturk       #+#    #+#                 */
/*   Updated: 2024/02/06 11:12:03 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_arr(char **arr)
{
	int	i;

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
	if (data->file.identifier.path_no)
	{
		free(data->file.identifier.path_no);
		err_msg("Texture path is wrong");
	}
	if (data->file.identifier.path_so)
	{
		free(data->file.identifier.path_so);
		err_msg("Texture path is wrong");
	}
	if (data->file.identifier.path_we)
	{
		free(data->file.identifier.path_we);
		err_msg("Texture path is wrong");
	}
	if (data->file.identifier.path_ea)
	{
		free(data->file.identifier.path_ea);
		err_msg("Texture path is wrong");
	}
}

void	clean_textures(t_data *data)
{
	mlx_delete_texture(data->file.identifier.tex_no);
	mlx_delete_texture(data->file.identifier.tex_so);
	mlx_delete_texture(data->file.identifier.tex_we);
	mlx_delete_texture(data->file.identifier.tex_ea);
}

void	terminate_exit(t_data *data)
{
	mlx_terminate(data->mlx);
	exit(EXIT_SUCCESS);
}
