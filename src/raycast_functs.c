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
	if (!coordenate_collides(comp, comp->sight->x, comp->sight->y + 2)
		&& coordenate_collides(comp, comp->sight->x, comp->sight->y - 2))
	{
		comp->sight->pixels->wall_dir = N;
		return (comp->no);
	}
	if (!coordenate_collides(comp, comp->sight->x, comp->sight->y - 2)
		&& coordenate_collides(comp, comp->sight->x, comp->sight->y + 2))
	{
		comp->sight->pixels->wall_dir = S;
		return (comp->so);
	}
	if (!coordenate_collides(comp, comp->sight->x + 2, comp->sight->y)
		&& coordenate_collides(comp, comp->sight->x - 2, comp->sight->y))
	{
		comp->sight->pixels->wall_dir = W;
		return (comp->we);
	}
	if (!coordenate_collides(comp, comp->sight->x - 2, comp->sight->y)
		&& coordenate_collides(comp, comp->sight->x + 2, comp->sight->y))
	{
		comp->sight->pixels->wall_dir = E;
		return (comp->ea);
	}
	return(comp->no);
}

int	get_image_pixel(double x, double y, double height, t_compass *comp)
{
	int		pix;
	int		piy;
	int		res;
	mlx_image_t	*image;

	image = get_dir_wall(comp);
	if(comp->sight->pixels->wall_dir == N)
	{
		x = ((int)(comp->sight->x) % SQUARE_SIZE) + 0.5;
		pix = ((x) / (SQUARE_SIZE)) * (image->width);
		piy = (y / height) * (image->height);
		res = ((piy - 1 ) * image->width) + pix;
		return(comp->sight->pixels->no_pix[res]);
	}
	if(comp->sight->pixels->wall_dir == E)
	{
		x = ((int)(comp->sight->y) % SQUARE_SIZE) + 0.5;
		pix = ((x) / (SQUARE_SIZE)) * (image->width);
		piy = (y / height) * (image->height);
		res = ((piy - 1 ) * image->width) + pix;
		return(comp->sight->pixels->ea_pix[res]);
	}
	if(comp->sight->pixels->wall_dir == S)
	{
		x = ((int)(comp->sight->x) % SQUARE_SIZE) + 0.5;
		pix = ((x) / (SQUARE_SIZE)) * (image->width);
		piy = (y / height) * (image->height);
		res = ((piy - 1 ) * image->width) - pix;
		return(comp->sight->pixels->so_pix[res]);
	}
	if(comp->sight->pixels->wall_dir == W)
	{
		x = ((int)(comp->sight->y) % SQUARE_SIZE) + 0.5;
		pix = ((x) / (SQUARE_SIZE)) * (image->width);
		piy = (y / height) * (image->height);
		res = ((piy - 1 ) * image->width) - pix;
		return(comp->sight->pixels->we_pix[res]);
	}
	return (0);
}

void	draw_from_centre(int y, int start_x, int height, t_compass *comp)
{
	int invert;
	int	save;
	int	color = 0xFFFF00FF;

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
