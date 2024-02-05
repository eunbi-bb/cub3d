/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozturk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:04:11 by gozturk           #+#    #+#             */
/*   Updated: 2024/01/31 12:04:13 by gozturk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	valid_floor_color(t_file *file)
{
	if (file->identifier.f_r > 255 || file->identifier.f_r < 0)
		return (false);
	if (file->identifier.f_g > 255 || file->identifier.f_g < 0)
		return (false);
	if (file->identifier.f_b > 255 || file->identifier.f_b < 0)
		return (false);
	return (true);
}

bool	valid_ceiling_color(t_file *file)
{
	if (file->identifier.c_r > 255 || file->identifier.c_r < 0)
		return (false);
	if (file->identifier.c_g > 255 || file->identifier.c_g < 0)
		return (false);
	if (file->identifier.c_b > 255 || file->identifier.c_b < 0)
		return (false);
	return (true);
}

static void	floor_setter(t_file *file, char **color_arr)
{
	file->identifier.f_r = ft_atoi(color_arr[0]);
	file->identifier.f_g = ft_atoi(color_arr[1]);
	file->identifier.f_b = ft_atoi(color_arr[2]);
	file->identifier.floor_set = true;
}

static void	ceiling_setter(t_file *file, char **color_arr)
{
	file->identifier.c_r = ft_atoi(color_arr[0]);
	file->identifier.c_g = ft_atoi(color_arr[1]);
	file->identifier.c_b = ft_atoi(color_arr[2]);
	file->identifier.ceiling_set = true;
}

void	color_atoi(t_file *file, char **color_arr, char identifier_type)
{
	int	i;

	i = 0;
	while (color_arr[i] != NULL)
	{
		if (i > 2)
			err_msg("Wrong number of color");
		i++;
	}
	if (color_arr[0] == NULL || color_arr[1] == NULL
		|| color_arr[2] == NULL)
		err_msg("Color value is missing");
	if (identifier_type == 'f')
		floor_setter(file, color_arr);
	else
		ceiling_setter(file, color_arr);
}
