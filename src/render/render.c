#include "cub3d.h"

void	init_values(t_data *data, double ray)
{
	data->wall.xstep = sign(cos(ray));  /* +1 (right), 0 (no change), -1 (left) */
	data->wall.ystep = sign(sin(ray));  /* +1 (up),    0 (no change), -1 (down) */
	if (data->wall.xstep == 0)
		data->wall.xslope = INFINITY;
	else
		data->wall.xslope = tan(ray);
	if (data->wall.ystep == 0)
		data->wall.yslope = INFINITY;
	else
		data->wall.yslope = 1./tan(ray);
	if (data->wall.xstep > 0)
    	data->wall.nx = floor(data->player->x) + 1;
	else if (data->wall.xstep < 0)
    	data->wall.nx = ceil(data->player->x) - 1;
	else 
    	data->wall.nx = data->player->x;
	if (data->wall.ystep > 0)
    	data->wall.ny = floor(data->player->y) + 1;
	else if (data->wall.ystep < 0)
		data->wall.ny = ceil(data->player->y) - 1;
	else
    	data->wall.ny = data->player->y;
	data->wall.f = INFINITY;
	data->wall.g = INFINITY;
}

/*
*	Casting a single ray. 
*	ANGLE_PER_PIXEL = FOV_H / (SX - 1)
*/
double cast_single_ray(int x, t_data *data, t_dir *wall_dir)
{
	double	ray;
	double	wall_dist;
	int		fov_h;

	fov_h = deg2rad(FOV);
	ray = (data->player->th + (fov_h / 2.0)) - (x * (fov_h / (SX - 1.)));
	if (get_intersection(data, ray, wall_dir) == false)
		return (INFINITY); /* no intersection - maybe bad map? */
	wall_dist = get_distance(data->player->x, data->player->y, data->wall.wall_x, data->wall.wall_y);
	wall_dist *= cos(data->player->th -ray);
	return (wall_dist);
}

void	render(t_data *data)
{
	int		x;
	t_dir	wall_dir;
	double	wall_dist;

	x = 0;
	while (x < SX)
	{
		wall_dist = cast_single_ray(x, data, &wall_dir);
		draw_wall(data, wall_dist, x, wall_dir);
		x++;
	}
}

void key_press(struct mlx_key_data keydata, void *game_data)
{
	keys_t key;
	t_data *data;
	int		rotate;

	key = keydata.key;
	data = (t_data *)game_data;
	if (key == MLX_KEY_ESCAPE)
		exit(EXIT_SUCCESS);
	if (key == MLX_KEY_W || key == MLX_KEY_A \
		|| key == MLX_KEY_S || key == MLX_KEY_D)
	{
		if (player_move(data, key, MOVE_UNIT) == 0)
			render(data);
	}
	else if (key == MLX_KEY_LEFT || key == MLX_KEY_RIGHT)
	{
		if (key == MLX_KEY_LEFT)
			rotate = 1;
		else
			rotate = -1;
		player_rotate(data, ROT_UNIT * rotate);
		render(data);
	}
}

/******** Rendering without textures ********/
// int wall_colors[4] = {COLOR_N, COLOR_E, COLOR_W, COLOR_S};

// /*
// *   First while loop: Drawing vertical lines from top to the first pixel of the wall.(Ceiling)
// *   Second while loop: Drawing vertical lines of the wall.
// *   Third while loop: Drawing vertical lines from the end of the wall to bottom.(Floor)
// */
// void    draw_ver_line(t_data *data, int x, int y_start, int y_end, long long color)
// {
// 	int	y;

// 	y = 0;
// 	while (y <= y_start)
// 	{
// 		mlx_put_pixel(data->image, x, y, color_ceiling_floor(data, 'c'));
// 		y++;
// 	}
// 	while (y <= y_end)
// 	{
// 		mlx_put_pixel(data->image, x, y, color);
// 		y++;
// 	}
//     while (y <= SY -1)
//     {
//         mlx_put_pixel(data->image, x, y, color_ceiling_floor(data, 'f'));
// 		y++;
// 	}
// 	// printf("draw ver line\n");
// }

// void    draw_wall(t_data *data, double wdist, int x, long long color)
// {
// 	int wh = get_wall_height(wdist);
// 	int y0 = (int)((SY - wh)/ 2.0);
// 	int y1 = y0 + wh - 1;

// 	int ystart = max(0, y0);
// 	int yend = min(SY - 1, y1);

// 	draw_ver_line(data, x, ystart, yend, color);
// }

// void	render(t_data *data)
// {
// 	load_textures(data);
// 	get_png_rgb(0, 0, data->file.identifier.texture_no);
// 	for( int x=0; x < SX; x++ ) 
// 	{
// 		t_dir	wdir;
// 		double	wdist;
// 		wdist = cast_single_ray(x, data, &wdir);
// 		draw_wall(data, wdist, x, wall_colors[wdir]);
// 	}
// }
