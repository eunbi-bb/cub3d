#include "cub3d.h"

void	init_player(t_data *data)
{
	data->player = (t_player *)malloc(sizeof(t_player));
	data->player->x = data->file.map.player_pos_x;
	data->player->y = data->file.map.player_pos_y;
	data->player->th = position_to_degree(data->file.map.p_direction);
			printf("**-----------------------------**\n");
			printf("*   data.px : %f    *\n", data->player->x);
			printf("*   data.py : %f    *\n", data->player->y);
			printf("*   data.pth: %f    *\n", data->player->th);
			printf("**-----------------------------**\n");
}

void init_identifiers(t_file *file)
{
	file->identifier.path_no_texture = NULL;
	file->identifier.no_set = false;
	file->identifier.path_so_texture = NULL;
	file->identifier.so_set = false;
	file->identifier.path_we_texture = NULL;
	file->identifier.we_set = false;
	file->identifier.path_ea_texture = NULL;
	file->identifier.ea_set = false;
	file->identifier.ceiling_set = false;
	file->identifier.floor_set = false;
	file->identifier.number_of_lines = 0;
	file->identifier.f_r = 0;
	file->identifier.f_g = 0;
	file->identifier.f_b = 0;
	file->identifier.c_r = 0;
	file->identifier.c_g = 0;
	file->identifier.c_b = 0;
}

void init_map(t_file *file)
{
	file->map.row = 0;
	file->map.column = 0;
	file->map.p_direction = '0';
	file->map.player_pos_x = -1;
	file->map.player_pos_y = -1;
	file->map.map_arr = NULL;
	file->map.copy_arr = NULL;
	file->map.map_int_arr = NULL;
}

void init_file_struct(t_file *file)
{
	file->total_lines = 0;
	file->content_arr = NULL;
	init_identifiers(file);
	init_map(file);
}