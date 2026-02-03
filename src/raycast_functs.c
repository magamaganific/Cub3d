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

void	get_image_pixel(float y, float height, t_compass *comp)
{
	// float	x;
	// x = get_wall_position(comp, y)

	(void)y;
	(void) height;
	unsigned int i = 0;
	int x = 0;
	int j = 0;

	while (i != comp->no->height * comp->no->width * 4)
	{
		while (j < 60)
		{
			while (x < 24)
			{
				mlx_put_pixel(comp->walls, x, j, comp->no->pixels[i]);
				printf("%d", comp->no->pixels[i]);
				i++;
				x++;
			}
			x = 0;
			j++;
		}
	}
}

// void	draw_from_centre(float y, float start_x, float height, t_compass *comp)
// {
// 	float width;
// 	float invert;
// 	float	save;
// 	int	color = 0xFFFF00FF;

// 	width = comp->bg->width / 60;
// 	invert = y - height;
// 	save = y;
// 	if (start_x < 0)
// 		return ;
// 	while (y > invert && y > 0)
// 	{
// 		mlx_put_pixel(comp->walls, start_x, y, color);
// 		y--;
// 	}
// 	y = save;
// 	while (y < comp->walls->height / 2 + height && y < comp->walls->height)
// 	{
// 		//	color = get_image_pixel(y, height, comp);
// 		mlx_put_pixel(comp->walls, start_x, y, 0xFFFF00FF);
// 		y++;
// 	}
// }

void	draw_pixel_pillar(t_compass *comp, float x, float y, float angle)
{
	float	width;
	float	height;
	float	raylength;
	float	start_x;

	width = comp->bg->width / 60;
	raylength = sqrt(powf(comp->sight->x - comp->player_x, 2) + powf(comp->sight->y
				- comp->player_y, 2));
	height = comp->walls->height / raylength * 9;
	start_x =((comp->sight->angle + 30) - angle) * width;
	start_x = comp->walls->width - start_x;
	// printf("raylength-> %f\n", raylength);
	// printf("height: %f\n", height);
	// printf("angle: %f\n", angle);
	// printf("main angle: %f\n", comp->sight->angle);
	// printf("start_x: %f\n", start_x);
	(void)x;
	y = comp->walls->height / 2;
	// draw_from_centre(y, start_x, height, comp);
	get_image_pixel(y, height, comp);
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
	// while (angle < comp->sight->angle + 30)
	// {
		reset_line_to_player(comp, angle);
		while (!coordenate_collides(comp, comp->sight->x, comp->sight->y))
		{
			mlx_put_pixel(comp->raymap, comp->sight->x, comp->sight->y, FOV);
			comp->sight->x += comp->sight->cos;
			comp->sight->y += comp->sight->sin;
		}
		draw_pixel_pillar(comp, 0, 0, angle);
	// 	angle += 20.0 / comp->walls->width ;
	// }
}
