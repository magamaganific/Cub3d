/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_functs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:17:01 by mfornovi          #+#    #+#             */
/*   Updated: 2026/02/24 18:06:51 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

// int	get_image_pixel(double x, double y, double height, t_compass *comp)
// {
// 	int			pix;
// 	int			piy;
// 	int			res;
// 	mlx_image_t	*image;

// 	image = get_dir_wall(comp);
// 	if (comp->st->pix->wall_dir == N)
// 	{
// 		x = ((int)(comp->st->x) % SQUARE_SIZE) + 0.5;
// 		pix = ((x) / (SQUARE_SIZE)) * (image->width);
// 		piy = (y / height) * (image->height);
// 		res = ((piy - 1) * image->width) + pix;
// 		return (comp->st->pix->no[res]);
// 	}
// 	if (comp->st->pix->wall_dir == E)
// 	{
// 		x = ((int)(comp->st->y) % SQUARE_SIZE) + 0.5;
// 		pix = ((x) / (SQUARE_SIZE)) * (image->width);
// 		piy = (y / height) * (image->height);
// 		res = ((piy - 1) * image->width) + pix;
// 		return (comp->st->pix->ea[res]);
// 	}
// 	if (comp->st->pix->wall_dir == S)
// 	{
// 		x = ((int)(comp->st->x) % SQUARE_SIZE) + 0.5;
// 		pix = ((x) / (SQUARE_SIZE)) * (image->width);
// 		piy = (y / height) * (image->height);
// 		res = ((piy - 1) * image->width) - pix;
// 		return (comp->st->pix->so[res]);
// 	}
// 	if (comp->st->pix->wall_dir == W)
// 	{
// 		x = ((int)(comp->st->y) % SQUARE_SIZE) + 0.5;
// 		pix = ((x) / (SQUARE_SIZE)) * (image->width);
// 		piy = (y / height) * (image->height);
// 		res = ((piy - 1) * image->width) - pix;
// 		return (comp->st->pix->we[res]);
// 	}
// 	return (0);
// }

void	draw_from_centre(int y, int start_x, int height, t_compass *comp)
{
	int	invert;
	int	save;
	int	color;

	color = 0xFFFF00FF;
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
	while (y <= (int)comp->walls->height / 2 + height
		&& y <= (int)comp->walls->height)
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
	int		start_x;

	width = (double)comp->walls->width / 60;
	raylength = sqrt(powf(comp->st->x - comp->player_x, 2)
			+ powf(comp->st->y - comp->player_y, 2));
	raylength = (raylength * cos(degree_to_radians(angle
					- comp->st->angle)));
	height = (int)(comp->walls->height / raylength * 19);
	start_x = ((comp->st->angle + 30) - angle) * width;
	start_x = comp->walls->width - start_x;
	(void)x;
	y = comp->walls->height / 2;
	draw_from_centre(y, start_x, height, comp);
}

void	draw_raycaster(t_compass *comp)
{
	double	angle;

	clear_raycast(comp);
	save_angle_data(comp, &angle);
	while (angle < comp->st->angle + 30)
	{
		reset_line_to_player(comp, angle);
		while (!coordenate_collides(comp, comp->st->x, comp->st->y))
		{
			while (((int)comp->st->x % SQUARE_SIZE)
				&& ((int)comp->st->y % SQUARE_SIZE))
			{
				comp->st->x += comp->st->cos;
				comp->st->y += comp->st->sin;
			}
			if (coordenate_collides(comp, comp->st->x, comp->st->y))
				break ;
			comp->st->x += comp->st->cos;
			comp->st->y += comp->st->sin;
		}
		comp->st->pix->angle = angle;
		draw_pixel_pillar(comp, 0, 0, angle);
		angle += 50.0 / comp->walls->width ;
	}
}
