/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:09:44 by frlorenz          #+#    #+#             */
/*   Updated: 2025/12/11 18:16:37 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static void ft_initial_print(t_game *game)
{
	int x;
	int y;
	
	x = 0;
	while (x < game->mlx->width)
	{
		y = 0;
		while (y < (game->mlx->height / 2))
		{
			mlx_put_pixel(game->back, x, y, 0x33CCFFFF);
			y++;
		}
		while (y < game->mlx->height)
		{
			mlx_put_pixel(game->back, x, y, 0x006600FF);
			y++;
		}
		x++;
	}
	ft_draw_map(game);
	ft_draw_square(game->player.x, game->player.y, 10, 0xFF0000FF, game->front);
}

static void ft_hook(void * param)
{
	const t_game *game;
	
	game = param;
	mlx_resize_image(game->back, game->mlx->width, game->mlx->height);
	mlx_resize_image(game->front, game->mlx->width, game->mlx->height);
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_game *game;
	
	game = param;
	ft_draw_square(game->player.x, game->player.y, 10, 0, game->front);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_REPEAT)
		game->player.y += 20;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_REPEAT)
		game->player.y -= 20;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_REPEAT)
		game->player.x += 20;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_REPEAT)
		game->player.x -= 20;
	ft_draw_square(game->player.x, game->player.y, 10, 0xFF0000FF, game->front);
}

void ft_draw_square(int x, int y, int size, int color, mlx_image_t *front)
{
	int i;

	i = 0;
	while (i <= size)
	{
		mlx_put_pixel(front, x + i, y, color);
		mlx_put_pixel(front, x, y + i, color);
		mlx_put_pixel(front, x + size, y + i, color);
		mlx_put_pixel(front, x + i, y + size, color);
		i++;
	}
}

void ft_init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
}

void ft_draw_map(t_game *game)
{
	int	x;
	int y;

	x = 0;
	while(game->map[x])
	{
		y = 0;
		while(game->map[x][y])
		{
			if(game->map[x][y] == '1')
				ft_draw_square( x * 64, y * 64, 10, 0xFF0000FF, game->front);
			y++;
		}
		x++;
	}
}

int	main(int argc, char **argv)
{
	(void) argv;
	t_game	*game;

	
	if(argc == 2)
	{
		game = (t_game*) malloc (sizeof(t_game *));
		if (!game)
			return(0);
		game->map = ft_get_map();
		game->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
		if (!game->mlx)
			ft_error();
		game->back = mlx_new_image(game->mlx, WIDTH, HEIGHT);
		if (!game->back || (mlx_image_to_window(game->mlx, game->back, 0, 0) < 0))
			ft_error();
		game->front = mlx_new_image(game->mlx, WIDTH, HEIGHT);
		if (!game->front || (mlx_image_to_window(game->mlx, game->front, 0, 0) < 0))
			ft_error();
		ft_init_player(&game->player);
		ft_initial_print(game);
		mlx_loop_hook(game->mlx, &ft_hook, game);
		mlx_key_hook(game->mlx, &my_keyhook, game);
		mlx_loop(game->mlx);
		mlx_terminate(game->mlx);
	}
	else
		printf("Error\n Numero de arguentos incorrecto");
	return (0);
}