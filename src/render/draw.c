#include "cub3d.h"

long long    color_ceiling_floor(t_data *data, char del)
{
    int		colors[3];

    if (del == 'c')
    {
        colors[0] = data->file.identifier.c_r;
        colors[1] = data->file.identifier.c_g;
        colors[2] = data->file.identifier.c_b;
    }
    else
    {
        colors[0] = data->file.identifier.f_r;
        colors[1] = data->file.identifier.f_g;
        colors[2] = data->file.identifier.f_b;
    }
    return (get_rgba(colors[0], colors[1], colors[2], 255));
}

void    draw_ver_line(t_data *data, int x)
{
	int	y;
	
	y = 0;
	while (y <= data->wall.y_start)
	{
		mlx_put_pixel(data->image, x, y, color_ceiling_floor(data, 'c'));
		y++;
	}
	y = data->wall.y_end;
    while (y <= SY - 1)
    {
        mlx_put_pixel(data->image, x, y, color_ceiling_floor(data, 'f'));
		y++;
	}
}

void    draw_wall(t_data *data, double wdist, int x, t_dir wall_dir)
{
	int		y0; 
	int		y1;
	double light;

	light = get_luminosity(data, wdist);
	data->wall.wall_h = get_wall_height(wdist);
	y0 = (int)((SY - data->wall.wall_h)/ 2.0);
	y1 = y0 + data->wall.wall_h - 1;
	data->wall.y_start = max(0, y0);
	data->wall.y_end = min(SY - 1, y1);
	print_texture(data, x, y0, wall_dir, light);
	draw_ver_line(data, x);
}