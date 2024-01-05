#include "cub3d.h"

int wall_colors[4] = {COLOR_N, COLOR_S, COLOR_E, COLOR_W};

int map_get_cell( int x, int y )
{
    return (x >= 0 && x < MAPX && y >= 0 && y < MAPY) ? map[x][y] : -1;
}

int get_wall_height( double dist )
{
    double fov_h = 2.0 * dist * tan(FOV_V/2.0);
    return (int)(SY * (WALL_H / fov_h)); /* in pixels */
}

void    draw_ver_line(int x, int y_start, int y_end, int color)
{
    int	y;

	y = y_start;
	while (y <= y_end)
	{
		mlx_put_pixel(image, x, y, color);
		y++;
	}
}

void    draw_wall(double wdist, int x, long long color)
{
    int wh = get_wall_height(wdist);
    int y0 = (int)((SY - wh)/ 2.0);
    int y1 = y0 + wh - 1;

    int ystart = max(0, y0);
    int yend = min(SY - 1, y1);
    draw_ver_line(x, ystart, yend, color);
}

void	render(double px, double py, double th)
{
	for( int x=0; x<SX; x++ ) 
	{
        dir_t wdir;
        double wdist = cast_single_ray(x, px, py, th, &wdir);
        draw_wall(wdist, x, wall_colors[wdir]);
    }
}