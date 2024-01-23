/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/22 15:22:24 by eucho         #+#    #+#                 */
/*   Updated: 2024/01/23 10:54:37 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
*	Combining rgba individual integer values into
*	a single 32 bit integer.
*/
int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	load_textures(t_data *data)
{
	data->file.identifier.tex_no = mlx_load_png(data->file.identifier.path_no);
	data->file.identifier.tex_so = mlx_load_png(data->file.identifier.path_so);
	data->file.identifier.tex_we = mlx_load_png(data->file.identifier.path_we);
	data->file.identifier.tex_ea = mlx_load_png(data->file.identifier.path_ea);
	if (data->file.identifier.tex_no == NULL
		|| data->file.identifier.tex_so == NULL
		|| data->file.identifier.tex_we == NULL
		|| data->file.identifier.tex_ea == NULL)
	{
		printf("no image\n");
		free_textures(data);
	}
}

mlx_texture_t	*texture_dir(t_data *data, t_dir wdir)
{
	if (wdir == DIR_N)
		return (data->file.identifier.tex_no);
	else if (wdir == DIR_E)
		return (data->file.identifier.tex_ea);
	else if (wdir == DIR_W)
		return (data->file.identifier.tex_we);
	else
		return (data->file.identifier.tex_so);
}

/*
*	Extracting rgba values from png image and returns 
*	a single integer.
*/
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

/*
*	Printing textures on walls depending on the wall direction.
*	Expressing perspective effect with 'fade_color()'.
*	'tex.x' represents a column of a texture
*	and 'tex.y' represents a row of a texture.
*/
void	print_tex(t_data *data, int x, int y0, t_dir wall_dir)
{
	mlx_texture_t	*tex;
	int				y;
	int				color;

	tex = texture_dir(data, wall_dir);
	if (wall_dir == DIR_W || wall_dir == DIR_E)
		data->tex.ratio = data->wall.wall_y - floor(data->wall.wall_y);
	else
		data->tex.ratio = data->wall.wall_x - floor(data->wall.wall_x);
	data->tex.x = (int)(data->tex.ratio * tex->width);
	y = data->wall.y_start;
	while (y <= data->wall.y_end)
	{
		data->tex.y = (int)(((double)(y - y0) *\
					tex->height / data->wall.wall_h));
		color = fade_color(get_png_rgb(data->tex.x, data->tex.y, tex),
				data->tex.light);
		mlx_put_pixel(data->image, x, y, color);
		y++;
	}
}
