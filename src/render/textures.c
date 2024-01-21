#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "cub3d.h"
#include "MLX42/MLX42_Int.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	load_textures(t_data *data) 
{
	data->file.identifier.texture_no = mlx_load_png(data->file.identifier.path_no_texture);
	data->file.identifier.texture_so = mlx_load_png(data->file.identifier.path_so_texture);
	data->file.identifier.texture_we = mlx_load_png(data->file.identifier.path_we_texture);
	data->file.identifier.texture_ea = mlx_load_png(data->file.identifier.path_ea_texture);
	if (data->file.identifier.texture_no == NULL || data->file.identifier.texture_so == NULL
		|| data->file.identifier.texture_we == NULL || data->file.identifier.texture_ea == NULL)
	{
		printf("no image\n");
		free_textures(data);
		//free_image(data, NULL);
	}
}

mlx_texture_t *texture_dir(t_data *data, t_dir wdir)
{
	if (wdir == DIR_N)
		return (data->file.identifier.texture_no);
	else if (wdir == DIR_E)
		return (data->file.identifier.texture_ea);
	else if (wdir == DIR_W)
		return (data->file.identifier.texture_we);
	else
		return (data->file.identifier.texture_so);
}

int	get_png_rgb(int x, int y, mlx_texture_t *image)
{
	int	index;
	int	max;

	max = image->height * image->width * image->bytes_per_pixel;
	index = ((y * image->width) + x) * (image->bytes_per_pixel);
	if (index >= max)
		return (0);
	return (get_rgba(
		image->pixels[index + 0],
		image->pixels[index + 1],
		image->pixels[index + 2],
		image->pixels[index + 3]));
}

void	print_texture(t_data *data, int x, int y0, t_dir wall_dir, double light)
{
	mlx_texture_t	*tex;
	int				y;
	int				color;

	tex = texture_dir(data, wall_dir);
	if (wall_dir == DIR_W || wall_dir == DIR_E)
		data->tex.ratio = data->wall.wall_y-floor(data->wall.wall_y);
	else
		data->tex.ratio = data->wall.wall_x-floor(data->wall.wall_x);
	data->tex.x = (int)(data->tex.ratio * tex->width); /* texture column*/
	y = data->wall.y_start;
	while (y <= data->wall.y_end)
	{
		data->tex.y = (int)(((double)(y - y0) * tex->height / data->wall.wall_h)); /* texture row */
		color = fade_color(get_png_rgb(data->tex.x, data->tex.y, tex), light);
		mlx_put_pixel(data->image, x, y, color);
		y++;
	}
}