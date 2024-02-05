/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozturk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:05:21 by gozturk           #+#    #+#             */
/*   Updated: 2024/01/31 12:05:24 by gozturk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_floor(t_file *file, char *content, char **texture_arr)
{
	char	**color_arr;
	char	*temp_arr;

	if (ft_strsame("F", texture_arr[0]) == 1)
	{
		if (file->identifier.floor_set == true)
			err_msg("Floor is already set");
		temp_arr = ft_substr(content, 2, ft_strlen(content) - 2);
		color_arr = ft_split(temp_arr, ',');
		free(temp_arr);
		color_atoi(file, color_arr, 'f');
		free_arr(color_arr);
		return (0);
	}
	return (EXIT_FAILURE);
}

static int	set_ceiling(t_file *file, char *content, char **texture_arr)
{
	char	**color_arr;
	char	*temp_arr;

	if (ft_strsame("C", texture_arr[0]) == 1)
	{
		if (file->identifier.ceiling_set == true)
			err_msg("Ceiling is already set");
		temp_arr = ft_substr(content, 2, ft_strlen(content) - 2);
		color_arr = ft_split(temp_arr, ',');
		free(temp_arr);
		color_atoi(file, color_arr, 'c');
		if (file->identifier.c_r == file->identifier.f_r
			&& file->identifier.c_g == file->identifier.f_g
			&& file->identifier.c_b == file->identifier.f_b)
			err_msg("Set different colors for ceiling and floor");
		free_arr(color_arr);
		return (0);
	}
	return (EXIT_FAILURE);
}

void	sign_checker(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (ft_isdigit(line[i]) == 0 && line[i] != ',')
			err_msg("Invalid sign in the identifiers");
		i++;
	}
}

void	set_colors(t_file *file, char *content, char **texture_arr)
{
	sign_checker(texture_arr[1]);
	if (set_floor(file, content, texture_arr) == 0)
	{
		if (valid_floor_color(file) == false)
			err_msg("Invalid color range for the floor");
		return ;
	}
	if (set_ceiling(file, content, texture_arr) == 0)
	{
		if (valid_ceiling_color(file) == false)
			err_msg("Invalid color range for the ceiling");
		return ;
	}
}
