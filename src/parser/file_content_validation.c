#include "cub3d.h"

/*
** Checks a char is a valid one for the map
*/
bool	check_valid_chars(char c)
{
	return (c == '1' || c == ' ' || c == '\n'
		|| c == 'N' || c == '0' || c == 'W'
		|| c == 'E' || c == 'S' || c == '\0');
}

/*
** Checks if chars in map are valid characters by traversing
** in map char by char
*/
bool	valid_map_content(t_file *file, char **map_arr)
{
	int	row;
	int	col;

	row = 0;
	if (file->map.row == 0)
		err_msg("There is no map information in file");
	while (row < file->map.row && map_arr[row] != NULL)
	{
		col = 0;
		while (map_arr[row][col] != '\0')
		{
			if (!check_valid_chars(map_arr[row][col]))
			{
				err_msg("Invalid map content");
			}
			col++;
		}
		row++;
	}
	return (true);
}

/*
** Checks first 6 rows of the file
** if it contains correct information. There shouldnt be
** any information other than path for texture files
** and floor-ceiling color.(no map content in 6 rows)
*/
bool	valid_content_order(t_file *file)
{
	int	c;
	int	r;

	r = 0;
	while (r < 6 && file->content_arr[r] != NULL)
	{
		if (file->content_arr[r][c] == '1')
			err_msg("Wrong content order");
		c = 0;
		while (file->content_arr[r][c] != '\0'
			&& file->content_arr[r][c] == ' ')
		{
			if (file->content_arr[r][c] != 'N'
				|| file->content_arr[r][c] != 'S'
				|| file->content_arr[r][c] != 'E'
				|| file->content_arr[r][c] != 'W'
				|| file->content_arr[r][c] != 'F'
				|| file->content_arr[r][c] != 'C')
				err_msg("Wrong content order");
			c++;
		}
		c = 0;
		r++;
	}
	return (true);
}

/*
** Combines all checks related to file
*/
void	last_check_content(t_file *file)
{
	if (identifiers_complete(file) == true)
		err_msg("Some identifiers are missing");
	valid_map_content(file, file->map.map_arr);
	find_player_pos(file, 0);
	copy_map(file);
	check_walls(file);
}
