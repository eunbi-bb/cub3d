#include "cub3d.h"

bool	valid_player(char c)
{
	return (c == 'N' || c == 'S'
			|| c == 'W' || c == 'E');
}

static bool has_empty_line(char *line)
{
	return (line[0] == '\n');
}

void	create_map(t_file *file, char *line, int *row)
{
	char	*trimmed_newline;

	//printf("line = %s\n", line);
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

void find_player_pos(t_file *file)
{
	int	r;
	int	c;
	int	player_count;

	r = 0;
	player_count = 0;
	while (r < file->map.row && file->map.map_arr[r] != NULL)
	{
		c = 0;
		while(file->map.map_arr[r][c] != '\0')
		{
			if (valid_player(file->map.map_arr[r][c]))
			{
				file->map.player_pos_r = r;
				file->map.player_pos_c = c;
				file->map.player_char = file->map.map_arr[r][c];
				player_count++;
			}
			c++;
		}
		r++;
	}
	if ((file->map.player_pos_r == -1
		&& file->map.player_pos_c == -1)
		|| player_count > 1)
		err_msg("Wrong number of player");
}