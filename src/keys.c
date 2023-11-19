#include "cub3d.h"

void	move_down(t_game *game)
{
		game->move++;
		game->y_p_location++;
}

void	move_up(t_game *game)
{
		game->move++;
		game->y_p_location--;
}
void	move_left(t_game *game)
{
		game->move++;
		game->x_p_location--;
}

void	move_right(t_game *game)
{
		game->move++;
		game->x_p_location++;
}
