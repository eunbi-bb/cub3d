#include "cub3d.h"
#include <errno.h>

int	err_msg(char *str)
{
	write(STDERR_FILENO, "Error\n", 6);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	exit (EXIT_FAILURE);
}

void	perror_exit(char *str)
{
	perror(str);
	exit(errno);
}
