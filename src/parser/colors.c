#include "cub3d.h"

bool	valid_floor_color(t_file *file)
{
	if (file->identifier.f_r > 255 || file->identifier.f_r < 0)
		return (false);
	if (file->identifier.f_g > 255 || file->identifier.f_g < 0)
		return (false);
	if (file->identifier.f_b > 255 || file->identifier.f_b < 0)
		return (false);
	return (true);
}

bool	valid_ceiling_color(t_file *file)
{
	if (file->identifier.c_r > 255 || file->identifier.c_r < 0)
		return (false);
	if (file->identifier.c_g > 255 || file->identifier.c_g < 0)
		return (false);
	if (file->identifier.c_b > 255 || file->identifier.c_b < 0)
		return (false);
	return (true);
}