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


void	player_hook(mlx_key_data_t keydata, void *param)
{
	t_compass	*comp;

	comp = (t_compass *)param;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
		comp->player->instances[0].y += PLAYER_SIZE / 2;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
		comp->player->instances[0].y -= PLAYER_SIZE / 2;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
		comp->player->instances[0].x += PLAYER_SIZE / 2;
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT
			|| keydata.action == MLX_PRESS))
		comp->player->instances[0].x -= PLAYER_SIZE / 2;
}
