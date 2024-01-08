#include "cub3d.h"

int main(int argc, char **argv)
{
	t_data data;

	if (argc != 2)
		err_msg("Wrong number of arguments");
	parser(argc, argv, &data.file);
		//err_msg("Parser has failded");
}