#include "cub3d.h"

static bool valid_map_rows(int r, int c, t_file *file)
{
	t_map	*map;

	map = &file->map;
	while (map->map_arr[r][c] != '\0')
	{
		if (map->map_arr[r][c] == '0'
			&& (map->map_arr[r][c - 1] == ' '
				|| map->map_arr[r][c + 1] == ' '))
			return (false);
		if (map->map_arr[r][c] == ' ')
		{
			if (r != 0
				&& (map->map_arr[r - 1][c] != ' ' && map->map_arr[r - 1][c] != '1'))
				return (false);
			if (r != file->map.row - 1
				&& (map->map_arr[r + 1][c] != ' ' && map->map_arr[r + 1][c] != '1'))
				return (false);
		}
		c++;
	}
	if (map->map_arr[r][c - 1] != '1')
		return (false);
	return (true);
}

static bool valid_left_side_map(t_file *file)
{
	int r;
	int c;

	r = 0;
	while (r < file->map.row && file->map.map_arr[r] != NULL)
	{
		c = 0;
		while (file->map.map_arr[r][c] != '\0')
		{
			if (file->map.map_arr[r][c] != '\0'
				&& file->map.map_arr[r][c] == ' ')
			{
				c++;
				continue ;
			}
			if (file->map.map_arr[r][c] == '1')
				break ;
			else
				return (false);
			// if (file->map.map_arr[r][c] != '1')
			//  return (false);
			c++;
		}
		r++;
	}
	return (true);
}

static bool valid_first_last_row(t_file *file)
{
	int c;

	c = 0;
	while (file->map.map_arr[0][c] != '\0')
	{
		if (file->map.map_arr[0][c] == '0')
			err_msg("Map is not enclosed");
		c++;
	}
	c = 0;
	while (file->map.map_arr[file->map.row - 1][c] != '\0')
	{
		if (file->map.map_arr[file->map.row - 1][c] == '0')
			err_msg("Map is not enclosed");
		c++;
	}
	return (true);
}

static void check_different_shapes(int r, t_file *file)
{
	int c;
	int len_cur_line;
	int len_next_line;

	c = 0;
	if (r == file->map.row - 1)
		return ;
	len_cur_line = ft_strlen(file->map.map_arr[r]);
	len_next_line = ft_strlen(file->map.map_arr[r + 1]);
	while (file->map.map_arr[r][c] != '\0')
	{
		if (file->map.map_arr[r][c] == '0'
			&& len_cur_line > len_next_line
			&& (file->map.map_arr[r + 1][c] != '0'
				&& file->map.map_arr[r + 1][c] != '1'
				&& file->map.map_arr[r + 1][c] !=
				file->map.p_direction))
		{
			// printf("%d %d\n", r, c);
			err_msg("SICTIK");
		}
		c++;
	}
}

void check_walls(t_file *file)
{
	int r;

	r = 0;
	valid_first_last_row(file);
	while (r < file->map.row && file->map.map_arr[r] != NULL)
	{
		if (!valid_map_rows(r, 0, file))
			err_msg("Map is not enclosed");
		check_different_shapes(r, file);
			// err_msg("Invalid first last map");
		r++;
	}
	if (!valid_left_side_map(file))
		err_msg("Left side walls are not is not enclosed");
	return ;
}
