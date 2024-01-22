#include "cub3d.h"

/* Light effect */
/*
*	Extracting individual RGB components.
*/
void decode_rgb(int color, int *r, int *g, int *b)
{
    *r = (color >> 16) & 0xFF;
    *g = (color >> 8) & 0xFF;
    *b = color & 0xFF;
}

/*
*	Combining RGB components into a single integer color representation.
*/
int encode_rgb(int r, int g, int b) 
{
    return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
}

/*
*   Adjusting the intensity of the color based on the light
*   and returning the modified rgb color. 
*/
int fade_color(int color, double light)
{
	int	r;
	int	g;
	int	b;

    if (light < 0) 
		light = 0;
    else if( light > 1 )
        light = 1;
    decode_rgb(color, &r, &g, &b);
	r = (int)(r * light);
    g = (int)(g * light);
    b = (int)(b * light);
    return (encode_rgb(r, g, b));
}

/*
*	Returning a value between 0 - 1 depending on dist.
*	map_xamax() and map_ymax() are getting the value of MAPX and MAPY.
*	static var is in order to reduce duplicated calculation and avoid using of const.
* 
*/
double get_luminosity(t_data *data, double dist)
{
    static double D;
    D = -1;
    if (D < 0)
        D = (data->file.map.row + data->file.map.column)/2.0;
    if (dist > D)
        return (0);
    else
        return (1. - dist/D);
}