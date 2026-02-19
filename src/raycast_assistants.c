/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_assistants.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 11:15:38 by mfornovi          #+#    #+#             */
/*   Updated: 2026/01/29 11:15:41 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

bool	coordenate_collides(t_compass *comp, double fx, double fy)
{
	int		x;
	int		y;
	double	c;
	double	s;

	x = (int) fx / SQUARE_SIZE;
	y = (int) fy / SQUARE_SIZE;
	c = comp->sight->cos;
	s = comp->sight->sin;
	if (x >= comp->map_width || y >= comp->map_height || x <= 0 || y <= 0)
		return (true);
	if ((comp->map_arr[y][x] == '1' || comp->map_arr[y][x] == ' '
		|| comp->map_arr[y][x] == '\n'|| !comp->map_arr[y][x]))
		return (true);
	if(comp->map_arr[y + 1][x] == '1' && (int)(fy + s) / SQUARE_SIZE == y + 1)
		return (true);
	if(comp->map_arr[y - 1][x] == '1' && (int)(fy - s) / SQUARE_SIZE == y - 1)
		return (true);
	if(comp->map_arr[y][x + 1] == '1' && (int)(fx + c) / SQUARE_SIZE == x + 1)
		return (true);
	if(comp->map_arr[y][x - 1] == '1' && (int)(fx - c) / SQUARE_SIZE == x - 1)
		return (true);
	return (false);
}

bool	corner_collide(t_compass *comp, double x, double y)
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

double	degree_to_radians(double degree)
{
	return (degree * M_PI / 180);
}

void	save_angle_data(t_compass *comp, double *angle)
{
	comp->sight->x = comp->player_x;
	comp->sight->y = comp->player_y;
	comp->sight->prev_x = comp->player_x;
	comp->sight->prev_y = comp->player_y;
	if (comp->sight->angle > 360)
		comp->sight->angle -= 360;
	if (comp->sight->angle < 0)
		comp->sight->angle += 360;
	*angle = comp->sight->angle - 30;
}

void	reset_line_to_player(t_compass *comp, double angle)
{
	comp->sight->cos = cos(degree_to_radians(angle));
	comp->sight->sin = sin(degree_to_radians(angle));
	comp->sight->x = comp->player_x;
	comp->sight->y = comp->player_y;
}
