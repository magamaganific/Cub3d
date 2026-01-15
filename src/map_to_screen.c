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
	comp->raymap = mlx_new_image(comp->mlx, (comp->map_width + 1) * SQUARE_SIZE,
			(comp->map_height + 1) * SQUARE_SIZE);
	if (!comp->raymap)
		error();
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

bool	coordenate_collides(t_compass *comp, float fx, float fy)
{
	int	x;
	int	y;

	x = (int) fx / 30;
	y = (int) fy / 30;
	if (x > comp->map_width || y > comp->map_height || x <= 0 || y <= 0)
		return (true);
	if (comp->map_arr[y][x] == '1' || comp->map_arr[y][x] == ' '
		|| comp->map_arr[y][x] == '\n' || !comp->map_arr[y][x])
		return (true);
	return (false);
}

bool	corner_collide(t_compass *comp, float x, float y)
{
	if (coordenate_collides(comp, x, y)
		|| coordenate_collides(comp, x + HALF, y)
		|| coordenate_collides(comp, x, y + HALF)
		|| coordenate_collides(comp, x + HALF, y + HALF)
		|| coordenate_collides(comp, x, y)
		|| coordenate_collides(comp, x - HALF, y)
		|| coordenate_collides(comp, x, y - HALF)
		|| coordenate_collides(comp, x - HALF, y - HALF))
		return (true);
	return (false);
}

void	move_forward(t_compass *comp)
{
	float	angle;
	float	m_cos;
	float	m_sin;

	angle = comp->sight->angle;
	m_cos = cos(degree_to_radians(angle)) * SPEED;
	m_sin = sin(degree_to_radians(angle)) * SPEED;
	if (!corner_collide(comp, comp->player_x + m_cos, comp->player_y + m_sin))
	{
		comp->player_x += m_cos;
		comp->player_y += m_sin;
		draw_raycaster(comp);
		comp->player->instances[0].x = comp->player_x - HALF;
		comp->player->instances[0].y = comp->player_y - HALF;
	}
}

void	move_backwards(t_compass *comp)
{
	float	angle;
	float	m_cos;
	float	m_sin;

	angle = comp->sight->angle;
	m_cos = cos(degree_to_radians(angle - 180)) * SPEED;
	m_sin = sin(degree_to_radians(angle - 180)) * SPEED;
	if (!corner_collide(comp, comp->player_x + m_cos, comp->player_y + m_sin))
	{
		comp->player_x += m_cos;
		comp->player_y += m_sin;
		draw_raycaster(comp);
		comp->player->instances[0].x = comp->player_x - HALF;
		comp->player->instances[0].y = comp->player_y - HALF;
	}
}

void	move_right(t_compass *comp)
{
	float	angle;
	float	m_cos;
	float	m_sin;

	angle = comp->sight->angle;
	m_cos = cos(degree_to_radians(angle + 90)) * SPEED;
	m_sin = sin(degree_to_radians(angle + 90)) * SPEED;
	if (!corner_collide(comp, comp->player_x + m_cos, comp->player_y + m_sin))
	{
		comp->player_x += m_cos;
		comp->player_y += m_sin;
		draw_raycaster(comp);
		comp->player->instances[0].x = comp->player_x - HALF;
		comp->player->instances[0].y = comp->player_y - HALF;
	}
}

void	move_left(t_compass *comp)
{
	float	angle;
	float	m_cos;
	float	m_sin;

	angle = comp->sight->angle;
	m_cos = cos(degree_to_radians(angle - 90)) * SPEED;
	m_sin = sin(degree_to_radians(angle - 90)) * SPEED;
	if (!corner_collide(comp, comp->player_x + m_cos, comp->player_y + m_sin))
	{
		comp->player_x += m_cos;
		comp->player_y += m_sin;
		draw_raycaster(comp);
		comp->player->instances[0].x = comp->player_x - HALF;
		comp->player->instances[0].y = comp->player_y - HALF;
	}
}
void	erase_previous_ray(t_compass *comp)
{
	while (1)
	{
		while ((int)comp->prev_sight_x % SQUARE_SIZE != 0
			&& (int)comp->prev_sight_y % SQUARE_SIZE)
		{
			mlx_put_pixel(comp->raymap, comp->prev_sight_x, comp->prev_sight_y, 0);
			comp->prev_sight_x += comp->sight->cos;
			comp->prev_sight_y += comp->sight->sin;
		}
		if (!coordenate_collides(comp, comp->prev_sight_x + comp->sight->cos,
				comp->prev_sight_y + comp->sight->sin))
		{
			mlx_put_pixel(comp->raymap, comp->prev_sight_x, comp->prev_sight_y, 0);
			comp->prev_sight_x += comp->sight->cos;
			comp->prev_sight_y += comp->sight->sin;
		}
		else
			break ;
	}
}

void	player_hook(void *param)
{
	t_compass	*comp;

	comp = (t_compass *)param;
	if (mlx_is_key_down(comp->mlx, MLX_KEY_W))
		move_forward(comp);
	if (mlx_is_key_down(comp->mlx, MLX_KEY_S))
		move_backwards(comp);
	if (mlx_is_key_down(comp->mlx, MLX_KEY_D))
		move_right(comp);
	if (mlx_is_key_down(comp->mlx, MLX_KEY_A))
		move_left(comp);
	if (mlx_is_key_down(comp->mlx, MLX_KEY_LEFT))
	{
		comp->sight->angle -= 3;
		draw_raycaster(comp);
	}
	if (mlx_is_key_down(comp->mlx, MLX_KEY_RIGHT))
	{
		comp->sight->angle += 3;
		draw_raycaster(comp);
	}
}

float	degree_to_radians(float degree)
{
	return (degree * M_PI / 180);
}

void	draw_raycaster(t_compass *comp)
{
	erase_previous_ray(comp);
	comp->sight_x = comp->player_x;
	comp->sight_y = comp->player_y;
	comp->prev_sight_x = comp->player_x;
	comp->prev_sight_y = comp->player_y;
	comp->sight->cos = cos(degree_to_radians(comp->sight->angle));
	comp->sight->sin = sin(degree_to_radians(comp->sight->angle));
	while (1)
	{
		while ((int)comp->sight_x % SQUARE_SIZE != 0
			&& (int)comp->sight_y % SQUARE_SIZE)
		{
			mlx_put_pixel(comp->raymap, comp->sight_x, comp->sight_y, 0x0000FFFF);
			comp->sight_x += comp->sight->cos;
			comp->sight_y += comp->sight->sin;
		}
		if (!coordenate_collides(comp, comp->sight_x + comp->sight->cos,
				comp->sight_y + comp->sight->sin))
		{
			mlx_put_pixel(comp->raymap, comp->sight_x, comp->sight_y, 0x0000FFFF);
			comp->sight_x += comp->sight->cos;
			comp->sight_y += comp->sight->sin;
		}
		else
			break ;
	}
}

void	game_to_window(t_compass *comp)
{
	mlx_image_to_window(comp->mlx, comp->bg, 0, 0);
	mlx_image_to_window(comp->mlx, comp->map, 0, 0);
	mlx_image_to_window(comp->mlx, comp->raymap, 0, 0);
	mlx_image_to_window(comp->mlx, comp->player,
		comp->player_x, comp->player_y);
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
	game_to_window(comp);
	comp->player_x += HALF;
	comp->player_y += HALF;
	draw_raycaster(comp);
	mlx_loop_hook(comp->mlx, player_hook, comp);
}
