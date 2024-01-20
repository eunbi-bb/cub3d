#include "cub3d.h"

// int	check_empty_new_line(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\n')
// 			if (str[i + 1] == '\n')
// 				return (1);
// 		i++;
// 	}
// 	return (0);
// }

/*
**	Appends a string to a existed string
**	Works like ft_strjoin
*/
static char	*append_line_to_map(char *content, char *line)
{
	int		line_i;
	int		map_i;
	char	*appended;

	if (content == NULL)
		content = protect_mem(ft_calloc((ft_strlen_protect(line) + 1),
					sizeof(char)));
	appended = protect_mem(ft_calloc(sizeof(char), ft_strlen_protect(content)
				+ ft_strlen_protect(line) + 1));
	map_i = 0;
	while (content[map_i] != '\0')
	{
		appended[map_i] = content[map_i];
		map_i++;
	}
	line_i = 0;
	while (line[line_i] != '\0')
		appended[map_i++] = line[line_i++];
	appended[map_i] = '\0';
	if (line)
		free(line);
	return (free(content), appended);
}

/*
**	Reads a line at a time from fd, valid line (with its \n)
**	will be appended to content
**	Since a map in array of strings format is needed,
**	the content will be splitted and stored in map->map_arr
*/
char	*file_content_arr(t_file *file, t_map *map, int fd)
{
	char	*content;
	char	*line;
	(void)map;

	content = NULL;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		content = append_line_to_map(content, line);
		file->total_lines++;
		if (content == NULL)
			err_msg("Line can not be appended");
	}
	//printf("raw content = %s", content);
	file->content_arr = ft_split(content, '\n');
	if (file->content_arr == NULL)
		err_msg("Map array can not be created");
	//free(content);
	return (content);
}

/*
** Checks if there is a empty blank in map part
** of the file.
** param1 = char array of file content
**
** It passes chars until it passes floor-color ceiling line,
** searches consecutive \n's after first row of the map,
*/
bool empty_line_in_map(char *content, int i)
{
	while (content[i] != '\0')
	{
		if (content[i] == 'C' || content[i] == 'F')
		{
			while (content[i] != '\n')
				i++;
			i++;
			if (content[i] == 'C' || content[i] == 'F')
			{
				while (content[i] != '\n' && content[i] != '\0')
					i++;
			}
			while (content[i] != '1' && content[i] != '\0')
				i++;
			while ((content[i] == '1') || (content[i] == ' ')
					|| (content[i] == '0') || content[i] == '\n'
					|| valid_player(content[i]))
			{
				if (content[i] == '\n' && content[i + 1] == '\n')
					err_msg("Empty line in the map");
				i++;
			}
		}
		i++;
	}
	return (free(content), false);
}

int get_content_from_file(t_file *file, char *file_name)
{
	int	fd;
	int	map_lines;
	char *content;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		err_msg("File can not be opened");
	content = file_content_arr(file, &file->map, fd);
	//file_content_arr(file, &file->map, fd);
	valid_content_order(file);
	//print_map(file);
	map_lines = file->total_lines - 5;
	file->map.map_arr = (char**)malloc(sizeof(char*) * map_lines);
	if (handle_content(file) == 1)
		err_msg("Identifiers can not be set");
	empty_line_in_map(content, 0);
	make_int_arr(file, file->map.row - 1, 0);
	// make_int_arr(file, 0, 0);
	//copy_map(file);
	//print_file_content(file);
	//print_texture_paths(file);
	//print_colors(file);
	//print_number_map_lines(file);
	//printf("map row = %d\n", file->map.row);
	print_int_map(file);
	return (0);
}