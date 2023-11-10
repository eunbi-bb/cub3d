#include "cub3d.h"

void	*key_hook(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		else if (keydata.key == MLX_KEY_W )
		{
			if (!worldMap[(int)(game->posX + game->dirX * game->moveSpeed)][(int)(game->posY)])
			game->posX += game->dirX * game->moveSpeed;
			if (!worldMap[(int)(game->posX)][(int)(game->posY + game->dirY * game->moveSpeed)])
			game->posY += game->dirY * game->moveSpeed;
		}
		else if (keydata.key == MLX_KEY_S)
		{
		if (!worldMap[(int)(game->posX - game->dirX * game->moveSpeed)][(int)(game->posY)])
			game->posX -= game->dirX * game->moveSpeed;
		if (!worldMap[(int)(game->posX)][(int)(game->posY - game->dirY * game->moveSpeed)])
			game->posY -= game->dirY * game->moveSpeed;
		}
		else if (keydata.key == MLX_KEY_D)
		{
			//both camera direction and camera plane must be rotated
			double oldDirX = game->dirX;
			game->dirX = game->dirX * cos(-game->rotSpeed) - game->dirY * sin(-game->rotSpeed);
			game->dirY = oldDirX * sin(-game->rotSpeed) + game->dirY * cos(-game->rotSpeed);
			double oldPlaneX = game->planeX;
			game->planeX = game->planeX * cos(-game->rotSpeed) - game->planeY * sin(-game->rotSpeed);
			game->planeY = oldPlaneX * sin(-game->rotSpeed) + game->planeY * cos(-game->rotSpeed);
		}
		else if (keydata.key == MLX_KEY_A)
		{
			//both camera direction and camera plane must be rotated
			double oldDirX = game->dirX;
			game->dirX = game->dirX * cos(game->rotSpeed) - game->dirY * sin(game->rotSpeed);
			game->dirY = oldDirX * sin(game->rotSpeed) + game->dirY * cos(game->rotSpeed);
			double oldPlaneX = game->planeX;
			game->planeX = game->planeX * cos(game->rotSpeed) - game->planeY * sin(game->rotSpeed);
			game->planeY = oldPlaneX * sin(game->rotSpeed) + game->planeY * cos(game->rotSpeed);
		};
	}
}

void	draw_vline(t_game *game, int x, int y_start, int y_end, int color)
{
	int	y;

	y = y_start;
	while (y <= y_end)
	{
		mlx_put_pixel(game->mlx, x, y, color);
		y++;
	}
}


void	calc(t_game *info)
{
	int	x;

	x = 0;
	while (x < SX)
	{
		double cameraX = 2 * x / (double)SX - 1;
		double rayDirX = info->dirX + info->planeX * cameraX;
		double rayDirY = info->dirY + info->planeY * cameraX;
		
		int mapX = (int)info->posX;
		int mapY = (int)info->posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		
		 //length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (info->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0) hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(SY / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + SY / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + SY / 2;
		if(drawEnd >= SY)
			drawEnd = SY - 1;

		int	color;
		if (worldMap[mapY][mapX] == 1)
			color = 0xFF0000;
		else if (worldMap[mapY][mapX] == 2)
			color = 0x00FF00;
		else if (worldMap[mapY][mapX] == 3)
			color = 0x0000FF;
		else if (worldMap[mapY][mapX] == 4)
			color = 0xFFFFFF;
		else
			color = 0xFFFF00;
		
		if (side == 1)
			color = color / 2;

		draw_vline(info, x, drawStart, drawEnd, color);
		
		x++;
	}
}


void	*main_loop(t_game *game)
{
	calc(game);
}

int	main()
{
	t_game	game;

	// if (argc != 2)
	// 	err_msg(ERR_INPUT);
	game.mlx = mlx_init(SX, SY, "cub3d", false);
	game.posX = 12;
	game.posY = 5;
	game.dirX = -1;
	game.dirY = 0;
	game.planeX = 0;
	game.planeY = 0.66;
	game.moveSpeed = 0.05;
	game.rotSpeed = 0.05;
	// game.win = mlx_new_window(game.mlx, SX, SY, "cub3d");
	mlx_loop_hook(game.mlx, main_loop, &game);
	mlx_key_hook(game.win, key_hook, &game);

	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}