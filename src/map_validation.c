#include "cub3d.h"

char **copy_map(t_file *file)
{
	int	i;

	i = 0;
	file->map.copy_arr = ft_calloc(file->map.row + 1, sizeof(char *));
	if (file->map.copy_arr == NULL)
		err_msg("Malloc");
	while (i < file->map.row && file->map.map_arr[i] != NULL)
	{
		file->map.copy_arr[i] = ft_strdup(file->map.map_arr[i]);
		i++;
	}
	file->map.copy_arr[i] = NULL;
	return (file->map.copy_arr);
}
