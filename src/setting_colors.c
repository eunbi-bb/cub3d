#include "cub3d.h"

static int set_floor(t_file *file, char *content, char **texture_arr)
{
	char **color_arr;
	char *temp_arr;

	if (ft_strsame("F", texture_arr[0]) == 1)
	{
		if (file->identifier.floor_set == true)
			err_msg("Floor is already set");
		temp_arr = ft_substr(content, 2, ft_strlen(content) - 2);
		color_arr = ft_split(temp_arr, ',');
		file->identifier.f_r = ft_atoi(color_arr[0]);
		file->identifier.f_g = ft_atoi(color_arr[1]);
		file->identifier.f_b = ft_atoi(color_arr[2]);
		file->identifier.floor_set = true;
		return (0);
	}
	return (EXIT_FAILURE);
}

static bool valid_floor_color(t_file *file)
{
	if (file->identifier.f_r > 255 || file->identifier.f_r < 0)
		return (false);
	if (file->identifier.f_g > 255 || file->identifier.f_g < 0)
		return (false);
	if (file->identifier.f_b > 255 || file->identifier.f_b < 0)
		return (false);
	return (true);
}

static bool valid_ceiling_color(t_file *file)
{
	if (file->identifier.c_r > 255 || file->identifier.c_r < 0)
		return (false);
	if (file->identifier.c_g > 255 || file->identifier.c_g < 0)
		return (false);
	if (file->identifier.c_b > 255 || file->identifier.c_b < 0)
		return (false);
	return (true);
}

static int set_ceiling(t_file *file, char *content, char **texture_arr)
{
	char **color_arr;
	char *temp_arr;

	if (ft_strsame("C", texture_arr[0]) == 1)
	{
		if (file->identifier.ceiling_set == true)
			err_msg("Ceiling is already set");
		temp_arr = ft_substr(content, 2, ft_strlen(content) - 2);
		color_arr = ft_split(temp_arr, ',');
		file->identifier.c_r = ft_atoi(color_arr[0]);
		file->identifier.c_g = ft_atoi(color_arr[1]);
		file->identifier.c_b = ft_atoi(color_arr[2]);
		file->identifier.ceiling_set = true;
		if (file->identifier.c_r == file->identifier.f_r
		&& file->identifier.c_g == file->identifier.f_g
		&& file->identifier.c_b == file->identifier.f_b)
			err_msg("Set different colors for ceiling and floor");
		return (0);
	}
	return (EXIT_FAILURE);
}

void set_colors(t_file *file, char *content, char **texture_arr)
{
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
