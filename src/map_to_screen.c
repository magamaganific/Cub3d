/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:40:06 by mfornovi          #+#    #+#             */
/*   Updated: 2026/01/09 11:40:08 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	ft_draw_square(int x, int y, int color, mlx_image_t *map)
{
	int	i;

	i = 0;
	while (i <= SQUARE_SIZE)
	{
		mlx_put_pixel(map, x + i, y, color);
		mlx_put_pixel(map, x, y + i, color);
		mlx_put_pixel(map, x + SQUARE_SIZE, y + i, color);
		mlx_put_pixel(map, x + i, y + SQUARE_SIZE, color);
		i++;
	}
}

void	init_player(t_compass *comp)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	comp->player = mlx_new_image(comp->mlx, PLAYER_SIZE + 1, PLAYER_SIZE + 1);
	if (!comp->player)
		error();
	while (x <= PLAYER_SIZE)
	{
		mlx_put_pixel(comp->player, x, 0, 0xFF0000FF);
		mlx_put_pixel(comp->player, x, PLAYER_SIZE, 0xFF0000FF);
		x++;
	}
	while (y <= PLAYER_SIZE)
	{
		mlx_put_pixel(comp->player, 0, y, 0xFF0000FF);
		mlx_put_pixel(comp->player, PLAYER_SIZE, y, 0xFF0000FF);
		y++;
	}
}

void	draw_minimap(t_compass *comp)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	comp->map = mlx_new_image(comp->mlx, (comp->map_width + 1) * SQUARE_SIZE,
			(comp->map_height + 1) * SQUARE_SIZE);
	if (!comp->map)
		error();
	while (y < comp->map_height)
	{
		x = 0;
		while (comp->map_arr[y][x])
		{
			if (comp->map_arr[y][x] == '1')
				ft_draw_square(x * SQUARE_SIZE, y * SQUARE_SIZE, 0xFF0000FF,
					comp->map);
			x++;
		}
		y++;
	}
	init_player(comp);
}

void	player_hook(mlx_key_data_t keydata, void *param)
{
	t_compass	*comp;

	comp = (t_compass *)param;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
		comp->player->instances[0].y += SPEED;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
		comp->player->instances[0].y -= SPEED;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
		comp->player->instances[0].x += SPEED;
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
		comp->player->instances[0].x -= SPEED;
}

void	startup_map(t_compass *comp)
{
	comp->bg = mlx_new_image(comp->mlx, WIDTH, HEIGHT);
	if (!comp->bg)
		error();
	comp->no = mlx_texture_to_image(comp->mlx, comp->no_text);
	if (!comp->no)
		error();
	comp->so = mlx_texture_to_image(comp->mlx, comp->so_text);
	if (!comp->so)
		error();
	comp->we = mlx_texture_to_image(comp->mlx, comp->we_text);
	if (!comp->we)
		error();
	comp->ea = mlx_texture_to_image(comp->mlx, comp->ea_text);
	if (!comp->ea)
		error();
	draw_minimap(comp);
	mlx_loop_hook(comp->mlx, set_bg, comp);
	mlx_image_to_window(comp->mlx, comp->bg, 0, 0);
	/* mlx_image_to_window(comp->mlx, comp->no, 0, 0);
	 mlx_image_to_window(comp->mlx, comp->so, 100, 0);
	 mlx_image_to_window(comp->mlx, comp->we, 0, 100);
	 mlx_image_to_window(comp->mlx, comp->ea, 100, 100);*/
	mlx_image_to_window(comp->mlx, comp->map, 0, 0);
	mlx_image_to_window(comp->mlx, comp->player,
		comp->player_x, comp->player_y);
	mlx_key_hook(comp->mlx, &player_hook, comp);
}
