#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "cub3d.h"
#include "MLX42/MLX42_Int.h"

   get_texture_side(t_dir *step, int *hit_side)
{
	if (*hit_side == VERT && step->DIR_S < 0)
		return (TXT_NORTH);
	if (*hit_side == VERT && step->DIR_N > 0)
		return (TXT_SOUTH);
	if (*hit_side == HORIZ && step->DIR_W < 0)
		return (TXT_EAST);
	if (*hit_side == HORIZ && step->DIR_E > 0)
		return (TXT_WEST);
	return (0);
}

	DIR_N=0,
	DIR_E, 
	DIR_W, 
	DIR_S 