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

void	erase_previous_raycast(t_compass *comp)
{
	float	x;
	float	y;
	
	x = 0;
	y = 0;
	while (y < comp->raymap->height - 30)
	{
		while (x < comp->raymap->width - 30)
		{
			mlx_put_pixel(comp->raymap, x, y, 0);
			x++;
		}
		x = 0;
		y++;
	}
}

float	degree_to_radians(float degree)
{
	return (degree * M_PI / 180);
}

void	save_angle_data(t_compass *comp, float *angle)
{
	comp->sight_x = comp->player_x;
	comp->sight_y = comp->player_y;
	comp->prev_sight_x = comp->player_x;
	comp->prev_sight_y = comp->player_y;
	if (comp->sight->angle > 360)
		comp->sight->angle -= 360;
	if (comp->sight->angle < 0)
		comp->sight->angle += 360;
	*angle = comp->sight->angle - 30;
}

void	reset_line_to_player(t_compass *comp, float angle)
{
	comp->sight->cos = cos(degree_to_radians(angle));
	comp->sight->sin = sin(degree_to_radians(angle));
	comp->sight_x = comp->player_x;
	comp->sight_y = comp->player_y;
}

void	draw_raycaster(t_compass *comp)
{
	float	angle;

	erase_previous_raycast(comp);
	save_angle_data(comp, &angle);
	while(angle < comp->sight->angle + 30)
	{
		reset_line_to_player(comp, angle);
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
		angle++;
	}
}
