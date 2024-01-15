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

/*
*   First while loop: Drawing vertical lines from top to the first pixel of the wall.(Ceiling)
*   Second while loop: Drawing vertical lines of the wall.
*   Third while loop: Drawing vertical lines from the end of the wall to bottom.(Floor)
*/
void    draw_ver_line(t_data *data, int x, int y_start, int y_end, long long color)
{
	int	y;

	y = 0;
	while (y <= y_start)
	{
		mlx_put_pixel(data->image, x, y, color_ceiling_floor(data, 'c'));
		y++;
	}
	while (y <= y_end)
	{
		mlx_put_pixel(data->image, x, y, color);
		y++;
	}
    while (y <= SY -1)
    {
        mlx_put_pixel(data->image, x, y, color_ceiling_floor(data, 'f'));
		y++;
	}
}

void    draw_wall(t_data *data, double wdist, int x, long long color)
{
	int wh = get_wall_height(wdist);
	int y0 = (int)((SY - wh)/ 2.0);
	int y1 = y0 + wh - 1;

	int ystart = max(0, y0);
	int yend = min(SY - 1, y1);

	draw_ver_line(data, x, ystart, yend, color);
}

void	render(t_data *data)
{
	for( int x=0; x < SX; x++ ) 
	{
		t_dir	wdir;
		double	wdist;
		wdist = cast_single_ray(x, data, &wdir);
		draw_wall(data, wdist, x, wall_colors[wdir]);
	}
}