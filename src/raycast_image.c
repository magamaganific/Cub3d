/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:57:28 by frlorenz          #+#    #+#             */
/*   Updated: 2026/02/27 10:34:51 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

mlx_image_t	*get_dir_wall(t_compass *comp)
{
	if (!coordenate_collides(comp, comp->st->x, comp->st->y + 2)
		&& coordenate_collides(comp, comp->st->x, comp->st->y - 2))
	{
		comp->st->pix->wall_dir = N;
		return (comp->no);
	}
	if (!coordenate_collides(comp, comp->st->x, comp->st->y - 2)
		&& coordenate_collides(comp, comp->st->x, comp->st->y + 2))
	{
		comp->st->pix->wall_dir = S;
		return (comp->so);
	}
	if (!coordenate_collides(comp, comp->st->x + 2, comp->st->y)
		&& coordenate_collides(comp, comp->st->x - 2, comp->st->y))
	{
		comp->st->pix->wall_dir = W;
		return (comp->we);
	}
	if (!coordenate_collides(comp, comp->st->x - 2, comp->st->y)
		&& coordenate_collides(comp, comp->st->x + 2, comp->st->y))
	{
		comp->st->pix->wall_dir = E;
		return (comp->ea);
	}
	return (comp->no);
}

int	get_pix(double x, mlx_image_t	*img, t_compass *comp)
{
	if (comp->st->pix->wall_dir == N)
		x = ((int)(comp->st->x) % SQUARE_SIZE);
	if (comp->st->pix->wall_dir == E)
		x = ((int)(comp->st->y) % SQUARE_SIZE);
	if (comp->st->pix->wall_dir == S)
		x = ((int)(comp->st->x) % SQUARE_SIZE);
	if (comp->st->pix->wall_dir == W)
		x = ((int)(comp->st->y) % SQUARE_SIZE);
	return ((int)(((x) / (SQUARE_SIZE)) * (img->width)));
}

int	get_image_pixel(double x, double y, double height, t_compass *comp)
{
	int			piy;
	mlx_image_t	*img;

	img = get_dir_wall(comp);
	piy = (y / height) * (img->height);
	if (piy <= 0)
		return (0);
	if (comp->st->pix->wall_dir == N && (int)(((piy - 1) * img->width)
		+ get_pix(x, img, comp)) <= comp->st->pix->no_size)
		return (comp->st->pix->no[(int)(((piy - 1) * img->width)
				+ get_pix(x, img, comp))]);
	if (comp->st->pix->wall_dir == E && (int)(((piy - 1) * img->width)
		+ get_pix(x, img, comp)) <= comp->st->pix->ea_size)
		return (comp->st->pix->ea[(int)(((piy - 1) * img->width)
				+ get_pix(x, img, comp))]);
	if (comp->st->pix->wall_dir == S && (int)((piy * img->width)
		- get_pix(x, img, comp)) <= comp->st->pix->so_size)
		return (comp->st->pix->so[(int)((piy * img->width)
				- get_pix(x, img, comp))]);
	if (comp->st->pix->wall_dir == W && (int)((piy * img->width)
		- get_pix(x, img, comp)) <= comp->st->pix->we_size)
		return (comp->st->pix->we[(int)((piy * img->width)
				- get_pix(x, img, comp))]);
	return (0);
}

void	clear_raycast(t_compass *comp)
{
	clear_image(comp->raymap);
	clear_image(comp->walls);
}
