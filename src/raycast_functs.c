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

void init_pixels_rgba(int **pixels, mlx_image_t *image)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int n;

	i = 0;
	j = 0;
	n = 0;
	while (i < image->height * image->width)
	{
		pixels[i] = (int *)ft_calloc(sizeof(int), 4);
		while(j < 4)
		{
			pixels[i][j] = image->pixels[n];
			j++;
			n++;
		}
		j = 0;
		i++;
	}
}

void	free_pixels_rgba(int **pixels, mlx_image_t *image)
{
	unsigned int	i;

	i = 0;
	while (i < image->height * image->width)
	{
		free(pixels[i]);
		i++;
	}
	free(pixels);
}

void	get_image_pixel(float x, float y, float height, mlx_image_t *image)
{
	// int	**pixels;
	float	pix;
	float	piy;

	// pixels = (int **)ft_calloc(sizeof(int *), image->height * image->width);
	// init_pixels_rgba(pixels, image);
	x = (int)x % SQUARE_SIZE;
	pix = (x / SQUARE_SIZE) * image->width;
	piy = (y / height) * image->height;

	// printf("image->width: %d, x: %f, pix-> %f\n", image->width, x, pix);
	// printf("image->height: %d, y: %f, piy-> %f\n", image->height, y, piy);
	// free_pixels_rgba(pixels, image);
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
	get_image_pixel(comp->sight->x, y, height, comp->no);
	y = comp->walls->height / 2;
	// draw_from_centre(y, start_x, height, comp);
}

void	clear_raycast(t_compass *comp)
{
	clear_image(comp->raymap);
	clear_image(comp->walls);
}

void	draw_raycaster(t_compass *comp)
{
	float	angle;

	// clear_raycast(comp);
	save_angle_data(comp, &angle);
	// while (angle < comp->sight->angle + 30)
	// {
		reset_line_to_player(comp, angle + 30);
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
