#include "cub3d.h"

bool is_texture_type(char *texture)
{
	return (ft_strsame(texture, "NO") == 1
		|| ft_strsame(texture, "SO") == 1
		|| ft_strsame(texture, "WE") == 1
		|| ft_strsame(texture, "EA") == 1);
}

bool is_color_type(char *color)
{
	return (ft_strsame(color, "F") == 1
		|| ft_strsame(color, "C") == 1);
}

bool identifiers_complete(t_file *file)
{
	return (file->identifier.no_set == false
			|| file->identifier.so_set == false
			|| file->identifier.we_set == false
			|| file->identifier.ea_set == false
			|| file->identifier.floor_set == false
			|| file->identifier.ceiling_set == false);
}

int handle_content(t_file *file)
{
	char **temp_arr;
	int	r;
	int row;

	r = 0;
	row = 0;
	temp_arr = NULL;
	while (file->content_arr[r] != NULL)
	{
		//printf("content_arr = %s\n %d\n", file->content_arr[r], r);
		temp_arr = ft_split(file->content_arr[r], ' ');
		//printf("temp_arr = %s\n", temp_arr[0]);
		//printf("content_arr = %s\n", file->content_arr[r]);
		// if (file->map.map_arr[row] != NULL && file->content_arr[r][0] == '\0')
		//  	err_msg("Empty line in the map");
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
		// printf("temp_arr = %s\n", temp_arr[0]);
		// if (temp_arr[0] != NULL)
	//	free_arr(temp_arr);
		r++;
	}
	last_check_content(file);
	return (EXIT_SUCCESS);
}