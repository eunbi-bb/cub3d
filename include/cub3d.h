#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include <stdio.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "MLX42/MLX42_Int.h"

#define  SX        	1200     /* screen width */
#define  SY         500    /* screen height */
#define  FOV        60      /* field of view (in degree) */
#define  FOV_H      deg2rad(FOV)
#define  FOV_V      (FOV_H*(double)SY/(double)SX)
#define  WALL_H     1.0

#define _2PI		6.28318530717958647692  /* 360 degrees */
#define	ROT_UNIT	0.03 /* rad */
#define	MOVE_UNIT	0.15

#define  EPS            (1e-06)
#define  is_zero(d)     (fabs(d) < EPS)
#define  deg2rad(d)     ((d)*M_PI/180.0)    /* degree to radian */
#define  rad2deg(d)     ((d)*180.0/M_PI)    /* radian to degree */
#define  min(a,b)       ((a)<(b)? (a):(b))
#define  max(a,b)       ((a)>(b)? (a):(b))

static const double ANGLE_PER_PIXEL = FOV_H / (SX-1.);
static const double FOVH_2 = FOV_H / 2.0;

#define COLOR_N     0x00ffafff // GREEN
#define COLOR_S     0xffffafff // YELLOW
#define COLOR_E     0xA585F5ff // VIOLET
#define COLOR_W     0x00d7d7ff // BLUE
#define COLOR_CEIL	0x008080ff
#define COLOR_FLOOR	0x008000ff

enum 
{ 
	VERT, 
	HORIZ 
};

typedef enum
{
	DIR_N = 0,
	DIR_E, 
	DIR_W, 
	DIR_S 
} t_dir;

typedef struct s_player{
    double x;
    double y;
    double th;
} t_player;

/* coord. of wall intersection point */
typedef	struct s_wall
{
	double	wall_x;
	double	wall_y;
	int		wall_h;
	int		y_start;
	int		y_end;
	int		xstep;  /* +1 (right), 0 (no change), -1 (left) */
	int		ystep;  /* +1 (up),    0 (no change), -1 (down) */
	double	xslope;
	double	yslope;
	double	nx; 	// nx and ny are the next intersection coordinates of a ray from (px,py)
	double	ny;
	double	f;
	double	g;
}	t_wall;

typedef struct s_texture
{
	double	ratio;
	int x;
	int y;
}	t_texture;

typedef struct s_identifier
{
	char	*path_no_texture;
	bool	no_set;
	char	*path_so_texture;
	bool	so_set;
	char	*path_we_texture;
	bool	we_set;
	char	*path_ea_texture;
	bool	ea_set;
	bool	ceiling_set;
	bool	floor_set;
	int		number_of_lines;
	int		f_r;
	int		f_g;
	int		f_b;
	int		c_r;
	int		c_g;
	int		c_b;
	mlx_t		*mlx;
	mlx_texture_t *texture_no;
	mlx_texture_t *texture_so;
	mlx_texture_t *texture_we;
	mlx_texture_t *texture_ea;
}	t_identifier;

typedef struct s_map
{
	int		row;
	int		column;
	char	p_direction;
	double	player_pos_x;
	double	player_pos_y;
	char	**map_arr;
	char	**copy_arr;
	int		**map_int_arr;
}	t_map;

typedef struct s_file
{
	char *file_extension;
	char **content_arr;
	int total_lines;
	t_identifier identifier;
	t_map map;
}	t_file;

typedef struct s_data
{
	t_file		file;
	t_player	*player;
	t_wall		wall;
	t_texture	tex;
	mlx_t		*mlx;
	mlx_image_t	*image;
}	t_data;


//PRINT STATEMENTS FOR TESTING PURPOSE
/*** test.c ***/
void print_file_content(t_file *file);
void print_texture_paths(t_file *file);
void print_colors(t_file *file);
void print_map(t_file *file);
void print_int_map(t_file *file);

/*** error.c ***/
int		err_msg(char *str);
void	perror_exit(char *str);

/*** main.c ***/
double	position_to_degree(char p_direction);

/*** init.c ***/
void	init_player(t_data *data);
void init_identifiers(t_file *file);
void init_map(t_file *file);
void init_file_struct(t_file *file);

/*** parser.c ***/
int parser(int argc, char **argv, t_file *file);

/*** handle_file.c ***/
int		check_empty_new_line(char *str);
char	*file_content_arr(t_file *file, t_map *map, int fd);
int		get_content_from_file(t_file *file, char *file_name);
bool empty_line_in_map(char *content, int i);

/*** map.c ***/
bool	valid_player(char c);
void	create_map(t_file *file, char *line, int *row);
int		handle_map(t_file *file);
void	find_player_pos(t_file *file);
void make_int_arr(t_file *file, int r, int c);

/*** map_validation.c ***/
char **copy_map(t_file *file);

/*** seperate_file_content.c ***/
bool is_texture_type(char *texture);
bool is_color_type(char *color);
bool identifiers_complete(t_file *file);
int handle_content(t_file *file);

/*** setting_texture_paths.c ***/
void set_textures(t_file *file, char **texture_arr);

/*** setting_colors.c ***/
void set_colors(t_file *file, char *content, char **texture_arr);

/*** file_extension.c ***/
bool valid_file_extension(char *extension, char *file_name);

/*** file_content_validation.c ***/
bool check_valid_chars(char c);
bool valid_map_content(t_file *file, char **map_arr);
bool valid_content_order(t_file *file);
void last_check_content(t_file *file);

/*** check_walls.c.c ***/
void check_walls(t_file *file);


/*** utils.c ***/
char	*protect_mem(char *str);
int		ft_strlen_protect(char *str);
int 	ft_strsame(const char *s1, const char *s2);
char	**array_dup(t_file *file, char **arr);

/*** free.c ***/
void	free_arr(char **arr);
void	free_textures(t_data *data);

/*** draw.c ***/
void    draw_wall(t_data *data, double wdist, int x, t_dir wall_dir);

/*** render.c ***/
void 	key_press(struct mlx_key_data keydata, void *user_data);
int 	get_cell_value(t_data *data, int x, int y);

/*** luminosity.c ***/
double	get_luminosity(t_data *data, double dist);
int		fade_color( int color, double lum );

/*** move.c ***/
int		player_move(t_data *data, int key, double amt);
void	player_rotate(t_data *data, double th);

/*** textures.c ***/
void			load_textures(t_data *data);
mlx_texture_t	*texture_dir(t_data *data, t_dir wdir);
int				get_rgba(int r, int g, int b, int a);

/*** ray_casting.c ***/
bool 	get_wall_intersection(t_data *data, double ray, t_dir *wall_dir);
double 	get_distance(double x0, double y0, double x1, double y1);

/*** render_utils.c ***/
void	init_values(t_data *data, double ray);
int		get_cell_value(t_data *data, int x, int y);
int		get_wall_height(double dist);

/*** render.c ***/
void	render(t_data *data);

/*** texture.c ***/
int		get_png_rgb(int x, int y, mlx_texture_t *image);
void	print_texture(t_data *data, int x, int y0, t_dir wall_dir, double light);

#endif
