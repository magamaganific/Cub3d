/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:57:28 by frlorenz          #+#    #+#             */
/*   Updated: 2026/02/25 10:48:59 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

mlx_image_t	*get_dir_wall(t_compass *comp)
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
	return (comp->no);
}

int	get_pix(double x, mlx_image_t	*img, t_compass *comp)
{
	if (comp->sight->pixels->wall_dir == N)
		x = ((int)(comp->sight->x) % SQUARE_SIZE) + 0.5;
	if (comp->sight->pixels->wall_dir == E)
		x = ((int)(comp->sight->y) % SQUARE_SIZE) + 0.5;
	if (comp->sight->pixels->wall_dir == S)
		x = ((int)(comp->sight->x) % SQUARE_SIZE) + 0.5;
	if (comp->sight->pixels->wall_dir == W)
		x = ((int)(comp->sight->y) % SQUARE_SIZE) + 0.5;
	return ((int)(((x) / (SQUARE_SIZE)) * (img->width)));
}

int	get_image_pixel(double x, double y, double height, t_compass *comp)
{
	int			piy;
	mlx_image_t	*img;

	img = get_dir_wall(comp);
	piy = (y / height) * (img->height);
	if (comp->sight->pixels->wall_dir == N)
		return (comp->sight->pixels->no_pix[(int)(((piy - 1) * img->width)
				+ get_pix(x, img, comp))]);
	if (comp->sight->pixels->wall_dir == E)
		return (comp->sight->pixels->ea_pix[(int)(((piy - 1) * img->width)
				+ get_pix(x, img, comp))]);
	if (comp->sight->pixels->wall_dir == S)
		return (comp->sight->pixels->so_pix[(int)(((piy - 1) * img->width)
				- get_pix(x, img, comp))]);
	if (comp->sight->pixels->wall_dir == W)
		return (comp->sight->pixels->we_pix[(int)(((piy - 1) * img->width)
				- get_pix(x, img, comp))]);
	return (0);
}

void	clear_raycast(t_compass *comp)
{
	clear_image(comp->raymap);
	clear_image(comp->walls);
}
