#include "cub3d.h"
#include <assert.h>

/*
**  PRINT STATEMENTS FOR TESTING PURPOSE
*/

void print_file_content(t_file *file)
{
	for(int i = 0; i < 20; i++)
	{
		printf("%s\n", file->content_arr[i]);
	}
	printf("file->total_lines = %d\n", file->total_lines);
	//printf("file content valid = %d\n", valid_file_content(file->map.map_arr));
	//assert(valid_file_content(file->map.map_arr) == 1);
}

void print_texture_paths(t_file *file)
{

	printf("texture path NO = %s\n", file->identifier.path_no_texture);
	printf("texture path SO = %s\n", file->identifier.path_so_texture);
	printf("texture path WE = %s\n", file->identifier.path_we_texture);
	printf("texture path EA = %s\n", file->identifier.path_ea_texture);
}

void print_colors(t_file *file)
{
	printf("colors floor = %d, %d, %d\n"
		, file->identifier.f_r, file->identifier.f_g, file->identifier.f_b);
	printf("colors ceiling = %d, %d, %d\n"
		, file->identifier.c_r, file->identifier.c_g, file->identifier.c_b);
}

void print_map(t_file *file)
{
	int i;

	i = 0;
	//printf("file->map.row = %d\n", file->map.row);
	//while (i < file->map.row)
	while (i < file->total_lines)
	{
		//printf("%s\n", file->map.copy_arr[i]);
		//printf("%s\n", file->map.map_arr[i]);
		printf("%s\n", file->content_arr[i]);
		i++;
	}
	printf("player r = %lf\nplayer c = %lf\nchar = %c\n"
		, file->map.player_pos_r, file->map.player_pos_c, file->map.player_char);
}