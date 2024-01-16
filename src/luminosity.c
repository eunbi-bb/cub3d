#include "cub3d.h"

/* Light effect */

void decode_color(int color, int *r, int *g, int *b) {
    *r = (color >> 16) & 0xFF;
    *g = (color >> 8) & 0xFF;
    *b = color & 0xFF;
}

int encode_color(int r, int g, int b) {
    return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
}

int fade_color( int color, double lum )
{
    if ( lum < 0 ) 
        lum = 0;
    else if( lum > 1 )
        lum = 1;
    int r, g, b;
    decode_color(color, &r, &g, &b);
    return encode_color( (int)(r*lum), (int)(g*lum), (int)(b*lum) );
}

/*
*	Returning a value between 0 - 1 depending on dist.
*	map_xamax() and map_ymax() are getting the value of MAPX and MAPY.
*	static var is in order to reduce duplicated calculation and avoid using of const.
* 
*/
double get_luminosity(t_data *data, double dist)
{
    static double D = -1;
    if( D < 0 ) D = (data->file.map.row + data->file.map.column)/2.0;
    return (dist > D) ? 0 : (1. - dist/D);
}