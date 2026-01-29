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

void	clear_image(mlx_image_t *image)
{
	float	x;
	float	y;

	x = 0;
	y = 0;
	while (y < image->height - 30)
	{
		while (x < image->width - 30)
		{
			mlx_put_pixel(image, x, y, 0);
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_pixel_pillar(t_compass *comp, float x, float y, float angle)
{
	float	width;
	float	distance;
	float	start_x;

	width = comp->bg->width / 60;
	distance = sqrt(pow(comp->sight->x - comp->player_x, 2) + pow(comp->sight->y
				- comp->player_y, 2));
	distance = distance * (cos(degree_to_radians(angle - comp->sight->angle)));
	start_x = x * width;
	while (y < distance)
	{
		while (x < width)
		{
			mlx_put_pixel(comp->walls, start_x + x, P_HEIGHT + y, WLL);
			x++;
		}
		x = 0;
		y++;
	}
}

void	clear_raycast(t_compass *comp)
{
	clear_image(comp->raymap);
	clear_image(comp->walls);
}

void	draw_raycaster(t_compass *comp)
{
	float	angle;

	clear_raycast(comp);
	save_angle_data(comp, &angle);
	while (angle < comp->sight->angle + 30)
	{
		reset_line_to_player(comp, angle);
		while (!coordenate_collides(comp, comp->sight->x + comp->sight->cos,
				comp->sight->y + comp->sight->sin))
		{
			while ((int)comp->sight->x % SQUARE_SIZE != 0
				&& (int)comp->sight->y % SQUARE_SIZE)
			{
				mlx_put_pixel(comp->raymap, comp->sight->x, comp->sight->y, FOV);
				draw_pixel_pillar(comp, comp->sight->angle + 30 - angle, 0, angle);
				comp->sight->x += comp->sight->cos;
				comp->sight->y += comp->sight->sin;
			}
			draw_pixel_pillar(comp, comp->sight->angle + 30 - angle, 0, angle);
			mlx_put_pixel(comp->raymap, comp->sight->x, comp->sight->y, FOV);
			comp->sight->x += comp->sight->cos;
			comp->sight->y += comp->sight->sin;
		}
		angle++;
	}
}
