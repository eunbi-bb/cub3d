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

void	color_atoi(t_file *file, char **color_arr, char identifier_type)
{
	if (color_arr[0] == NULL || color_arr[1] == NULL
		|| color_arr[2] == NULL)
		err_msg("Color value is missing");
	if (identifier_type == 'f')
	{
		file->identifier.f_r = ft_atoi(color_arr[0]);
		file->identifier.f_g = ft_atoi(color_arr[1]);
		file->identifier.f_b = ft_atoi(color_arr[2]);
		file->identifier.floor_set = true;
	}
	else
	{
		file->identifier.c_r = ft_atoi(color_arr[0]);
		file->identifier.c_g = ft_atoi(color_arr[1]);
		file->identifier.c_b = ft_atoi(color_arr[2]);
		file->identifier.ceiling_set = true;
	}
}
