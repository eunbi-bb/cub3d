/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seperate_file_content.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozturk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:05:12 by gozturk           #+#    #+#             */
/*   Updated: 2024/01/31 12:05:14 by gozturk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_texture_type(char *texture)
{
	return (ft_strsame(texture, "NO") == 1
		|| ft_strsame(texture, "SO") == 1
		|| ft_strsame(texture, "WE") == 1
		|| ft_strsame(texture, "EA") == 1);
}

bool	is_color_type(char *color)
{
	return (ft_strsame(color, "F") == 1
		|| ft_strsame(color, "C") == 1);
}

/*
** Checks if all directions and color identifiers are set
*/
bool	identifiers_complete(t_file *file)
{
	return (file->identifier.no_set == false
		|| file->identifier.so_set == false
		|| file->identifier.we_set == false
		|| file->identifier.ea_set == false
		|| file->identifier.floor_set == false
		|| file->identifier.ceiling_set == false);
}

/*
** Traverse in file content array (char arr) and seperates
** identifier information and creates map array
*/
int	handle_content(t_file *file, int r, int row)
{
	char	**temp_arr;

	temp_arr = NULL;
	while (file->content_arr[r] != NULL)
	{
		temp_arr = ft_split(file->content_arr[r], ' ');
		if (temp_arr == NULL)
			return (EXIT_FAILURE);
		if (is_texture_type(temp_arr[0]) == 1)
		{
			set_textures(file, temp_arr);
			free_arr(temp_arr);
		}
		else if (is_color_type(temp_arr[0]) == 1)
		{
			set_colors(file, file->content_arr[r], temp_arr);
			free_arr(temp_arr);
		}
		else
			create_map(file, file->content_arr[r], &row);
		r++;
	}
	last_check_content(file);
	return (EXIT_SUCCESS);
}
