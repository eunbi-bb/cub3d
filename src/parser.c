#include "cub3d.h"

int parser(int argc, char **argv, t_file *file)
{
	(void)argc;

	init_file_struct(file);
	valid_file_extension(".cub", argv[1]);
	get_content_from_file(file, argv[1]);
	return (0);
}