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
	while (y < image->height)
	{
		while (x < image->width)
		{
			mlx_put_pixel(image, x, y, 0);
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_up(float y, float start_x, float height, t_compass *comp)
{
	float width;
	float x;
	float invert;

	x = 0;
	width = comp->bg->width / 60;
	invert = y - height;
	while (y > invert)
	{
		while (x < width)
		{
			mlx_put_pixel(comp->walls, start_x + x, y, 0xFFFF00FF);
			x++;
		}
		x = 0;
		y--;
	}
}

void	draw_pixel_pillar(t_compass *comp, float x, float y, float angle)
{
	float	width;
	float	height;
	float	raylength;
	float	start_x;

	width = comp->bg->width / 60;
	raylength = sqrt(powf(comp->sight->x - comp->player_x, 2) + powf(comp->sight->y
				- comp->player_y, 2));
	height = comp->walls->height / raylength;
	start_x =(comp->sight->angle - angle + 30) * width;
	printf("raylength-> %f\n", raylength);
	printf("angle: %f\n", angle);
	printf("main angle: %f\n", comp->sight->angle);
	printf("start_x: %f\n", start_x);
	y = comp->walls->height / 2;
	draw_up(y, start_x, height, comp);
	while (y < comp->walls->height / 2 + height)
	{
		while (x < width)
		{
			mlx_put_pixel(comp->walls, start_x + x, y, 0xFFFF00FF);
			x++;
		}
		x = 0;
		y++;
	}
	// while (y < raylength)
	// {
	// 	while (x < width)
	// 	{
	// 		mlx_put_pixel(comp->walls, start_x + x, comp->walls->height / 2 + y, 0xFFFF00FF);
	// 		x++;
	// 	}
	// 	x = 0;
	// 	y++;
	// }
	// printf("y-> %f\n", y);
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
				comp->sight->x += comp->sight->cos;
				comp->sight->y += comp->sight->sin;
			}
			mlx_put_pixel(comp->raymap, comp->sight->x, comp->sight->y, FOV);
			comp->sight->x += comp->sight->cos;
			comp->sight->y += comp->sight->sin;
		}
		draw_pixel_pillar(comp, comp->sight->angle + 30 - angle, 0, angle + 30);
		angle++;
	}
}
