/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@42.fr>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/31 12:04:45 by gozturk       #+#    #+#                 */
/*   Updated: 2024/02/06 12:30:09 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	valid_player(char c)
{
	return (c == 'N' || c == 'S'
		|| c == 'W' || c == 'E');
}

static bool	has_empty_line(char *line)
{
	return (line[0] == '\n');
}

void	create_map(t_file *file, char *line, int *row)
{
	char	*trimmed_newline;

	if (has_empty_line(line))
		err_msg("Empty line in the map");
	trimmed_newline = ft_strtrim(line, "\n");
	file->map.map_arr[*row] = ft_strdup(trimmed_newline);
	free(trimmed_newline);
	trimmed_newline = NULL;
	*row = *row + 1;
	file->map.row++;
	file->map.column = ft_strlen(file->map.map_arr[0]);
}

void	find_player_pos(t_file *file, int r)
{
	int	c;
	int	player_count;

	player_count = 0;
	while (r < file->map.row && file->map.map_arr[r] != NULL)
	{
		c = 0;
		while (file->map.map_arr[r][c] != '\0')
		{
			if (valid_player(file->map.map_arr[r][c]))
			{
				file->map.player_pos_x = c;
				file->map.player_pos_y = file->map.row - r;
				file->map.p_direction = file->map.map_arr[r][c];
				file->map.map_arr[r][c] = '0';
				player_count++;
			}
			c++;
		}
		r++;
	}
	if ((file->map.player_pos_x == -1 && file->map.player_pos_y == -1)
		|| player_count > 1)
		err_msg("Wrong number of player");
}

/*
*	Modified to solve a mirrored map. It's copying into map_in_arr from bottom.
*/
void	make_int_arr(t_file *file, int r, int c)
{
	int	i;

	i = 0;
	file->map.map_int_arr = ft_calloc(file->map.row, sizeof(int *));
	if (file->map.map_int_arr == NULL)
		err_msg("Memory");
	while (r >= 0)
	{
		c = 0;
		file->map.map_int_arr[i]
			= ft_calloc((int)ft_strlen(file->map.map_arr[r]), sizeof(int));
		while (c < (int)ft_strlen(file->map.map_arr[r]))
		{
			if (file->map.map_arr[r][c] == '0')
				file->map.map_int_arr[i][c] = 0;
			else if (file->map.map_arr[r][c] != '1'
				&& file->map.map_arr[r][c] != '0')
				file->map.map_int_arr[i][c] = file->map.map_arr[r][c];
			else
				file->map.map_int_arr[i][c] = file->map.map_arr[r][c] - '0';
			c++;
		}
		i++;
		r--;
	}
}
