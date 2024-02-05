/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setting_texture_paths.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@42.fr>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 12:05:29 by gozturk       #+#    #+#                 */
/*   Updated: 2024/02/05 15:57:11 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_no_texture(t_file *file, char **texture_arr)
{
	if (ft_strsame(texture_arr[0], "NO") == 1)
	{
		if (file->identifier.no_set == true)
			err_msg("Path NO already set");
		// if (ft_strlen(texture_arr[1]) <= 0)
		// 	err_msg("Empty path");
		file->identifier.path_no = ft_strdup(texture_arr[1]);
		if (file->identifier.path_no == NULL)
			err_msg("set_NO_texture() has failed");
		file->identifier.no_set = true;
		return (0);
	}
	return (EXIT_FAILURE);
}

static int	set_so_texture(t_file *file, char **texture_arr)
{
	if (ft_strsame(texture_arr[0], "SO") == 1)
	{
		if (file->identifier.so_set == true)
			err_msg("Path SO already set");
		file->identifier.path_so = ft_strdup(texture_arr[1]);
		if (file->identifier.path_so == NULL)
			err_msg("set_SO_texture() has failed");
		file->identifier.so_set = true;
		return (0);
	}
	return (EXIT_FAILURE);
}

static int	set_we_texture(t_file *file, char **texture_arr)
{
	if (ft_strsame(texture_arr[0], "WE") == 1)
	{
		if (file->identifier.we_set == true)
			err_msg("Path WE already set");
		file->identifier.path_we = ft_strdup(texture_arr[1]);
		if (file->identifier.path_we == NULL)
			err_msg("set_WE_texture() has failed");
		file->identifier.we_set = true;
		return (0);
	}
	return (EXIT_FAILURE);
}

static int	set_ea_texture(t_file *file, char **texture_arr)
{
	if (ft_strsame(texture_arr[0], "EA") == 1)
	{
		if (file->identifier.ea_set == true)
			err_msg("Path EA already set");
		file->identifier.path_ea = ft_strdup(texture_arr[1]);
		if (file->identifier.path_ea == NULL)
			err_msg("set_EA_texture() has failed");
		file->identifier.ea_set = true;
		return (0);
	}
	return (EXIT_FAILURE);
}

void	set_textures(t_file *file, char **texture_arr)
{
	if(texture_arr[1] == NULL)
		err_msg("Empty Path");
	if (valid_file_extension(".png", texture_arr[1]) == 0)
		err_msg("Bad file extensiton in a texture path");
	if (set_no_texture(file, texture_arr) == 0)
		return ;
	if (set_so_texture(file, texture_arr) == 0)
		return ;
	if (set_we_texture(file, texture_arr) == 0)
		return ;
	if (set_ea_texture(file, texture_arr) == 0)
		return ;
}
