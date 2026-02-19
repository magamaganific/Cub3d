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
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < (int)image->height)
	{
		while (x < (int)image->width)
		{
			mlx_put_pixel(image, x, y, 0);
			x++;
		}
		x = 0;
		y++;
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

mlx_image_t *get_dir_wall(t_compass *comp)
{
	return(comp->no);
}

int	get_image_pixel(double x, double y, double height, t_compass *comp)
{
	int		pix;
	int		piy;
	int		res;
	mlx_image_t	*image;

	image = get_dir_wall(comp);
	x = ((int)(comp->sight->x) % SQUARE_SIZE) + 0.5;
	pix = ((x) / (SQUARE_SIZE)) * (image->width);
	piy = (y / height) * (image->height);
	res = 0;

	// printf("image->width: %d, x: %f, pix-> %d ", image->width, x, pix);
	// printf("height: %f, y: %f, piy-> %d\n", height, y, piy);
	// printf("comp->walls->height: %d, comp->so->width: %d, y: %f, piy-> %d, pix-> %d\n", comp->walls->height, comp->so->width, y, piy, pix);
	// printf("(piy - 1) * comp->so->width + pix = %d\n", ((piy - 1) * comp->so->width )+ pix);
	// printf("image->height: %d, y: %f, piy-> %d\n\n", image->height, y, piy);
	// printf("comp->walls->height: %d, height: %f, y-> %f\n", comp->walls->height, height, y);
	// res = (piy * image->width ) - pix; //south
	res = ((piy - 1 ) * image->width ) + pix; //north
	// printf("res: %d\n", res);
	return(comp->sight->pixels->no_pix[res]);
}

void	draw_from_centre(int y, int start_x, int height, t_compass *comp)
{
	// double width;
	int invert;
	int	save;
	int	color = 0xFFFF00FF;

	// width = comp->walls->width / 60;
	invert = y - height;
	save = y;
	if (start_x < 0)
		return ;
	while (y > invert && y > 0)
	{
		color = get_image_pixel(0, y - save + height, height * 2, comp);
		mlx_put_pixel(comp->walls, start_x, y, color);
		y--;
	}
	y = save;
	while (y < (int)comp->walls->height / 2 + height && y < (int)comp->walls->height)
	{
		color = get_image_pixel(0, y - save + height, height * 2, comp);
		mlx_put_pixel(comp->walls, start_x, y, color);
		y++;
	}
}

void	draw_pixel_pillar(t_compass *comp, double x, int y, double angle)
{
	double	width;
	double	height;
	double	raylength;
	int	start_x;

	width = (double)comp->walls->width / 60;
	raylength = sqrt(powf(comp->sight->x - comp->player_x, 2) + powf(comp->sight->y
				- comp->player_y, 2));
	raylength = (raylength * cos(degree_to_radians(angle - comp->sight->angle)));
	height = (int)(comp->walls->height / raylength * 19);
	start_x = ((comp->sight->angle + 30) - angle) * width;
	start_x = comp->walls->width - start_x;
	// printf("raylength-> %f, ", raylength);
	// printf("height: %f, ", height);
	// printf("angle: %f\n", angle);
	// printf("main angle: %f\n", comp->sight->angle);
	// printf("start_x: %f\n", start_x);
	(void)x;
	// get_image_pixel(comp->sight->x, y, height, comp);
	y = comp->walls->height / 2;
	draw_from_centre(y, start_x, height, comp);
}

void	clear_raycast(t_compass *comp)
{
	clear_image(comp->raymap);
	clear_image(comp->walls);
}

void	draw_raycaster(t_compass *comp)
{
	double	angle;

	clear_raycast(comp);
	save_angle_data(comp, &angle);
	while (angle < comp->sight->angle + 30)
	{
		reset_line_to_player(comp, angle);
		while (!coordenate_collides(comp, comp->sight->x, comp->sight->y))
		{
			while (((int)comp->sight->x % SQUARE_SIZE ) && ((int)comp->sight->y % SQUARE_SIZE ))
			{
				// mlx_put_pixel(comp->raymap, comp->sight->x, comp->sight->y, FOV);
				comp->sight->x += comp->sight->cos;
				comp->sight->y += comp->sight->sin;
			}
			if (coordenate_collides(comp, comp->sight->x, comp->sight->y))
				break;
			// mlx_put_pixel(comp->raymap, comp->sight->x, comp->sight->y, FOV);
			comp->sight->x += comp->sight->cos;
			comp->sight->y += comp->sight->sin;
		}
		comp->sight->pixels->angle = angle;
		draw_pixel_pillar(comp, 0, 0, angle);
		angle += 50.0 / comp->walls->width ;
	}
}
