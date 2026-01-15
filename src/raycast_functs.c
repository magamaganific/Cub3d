/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_functs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:17:01 by mfornovi          #+#    #+#             */
/*   Updated: 2026/01/15 12:17:03 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

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
		|| coordenate_collides(comp, x + HALF, y - HALF)
		|| coordenate_collides(comp, x, y + HALF)
		|| coordenate_collides(comp, x + HALF, y + HALF)
		|| coordenate_collides(comp, x, y)
		|| coordenate_collides(comp, x - HALF, y)
		|| coordenate_collides(comp, x - HALF, y + HALF)
		|| coordenate_collides(comp, x, y - HALF)
		|| coordenate_collides(comp, x - HALF, y - HALF))
		return (true);
	return (false);
}

void	erase_previous_ray(t_compass *comp)
{
	while (!coordenate_collides(comp, comp->prev_sight_x + comp->sight->cos,
			comp->prev_sight_y + comp->sight->sin))
	{
		while ((int)comp->prev_sight_x % SQUARE_SIZE != 0
			&& (int)comp->prev_sight_y % SQUARE_SIZE)
		{
			mlx_put_pixel(comp->raymap, comp->prev_sight_x,
				comp->prev_sight_y, 0);
			comp->prev_sight_x += comp->sight->cos;
			comp->prev_sight_y += comp->sight->sin;
		}
		mlx_put_pixel(comp->raymap, comp->prev_sight_x, comp->prev_sight_y, 0);
		comp->prev_sight_x += comp->sight->cos;
		comp->prev_sight_y += comp->sight->sin;
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
	while (!coordenate_collides(comp, comp->sight_x + comp->sight->cos,
			comp->sight_y + comp->sight->sin))
	{
		while ((int)comp->sight_x % SQUARE_SIZE != 0
			&& (int)comp->sight_y % SQUARE_SIZE)
		{
			mlx_put_pixel(comp->raymap, comp->sight_x,
				comp->sight_y, 0x0000FFFF);
			comp->sight_x += comp->sight->cos;
			comp->sight_y += comp->sight->sin;
		}
		mlx_put_pixel(comp->raymap, comp->sight_x, comp->sight_y, 0x0000FFFF);
		comp->sight_x += comp->sight->cos;
		comp->sight_y += comp->sight->sin;
	}
}
