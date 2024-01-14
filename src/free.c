#include "cub3d.h"

void	free_arr(char **arr)
{
	int i;

	i = 0;
	if (arr[i])
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
	}
	free(arr);
	arr = NULL;
}