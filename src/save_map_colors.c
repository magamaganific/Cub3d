/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 10:12:41 by mfornovi          #+#    #+#             */
/*   Updated: 2026/02/24 13:01:58 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	save_north_colors(t_compass *comp, int i, int size)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = 0;
	g = 0;
	b = 0;
	a = 0;
	size = i * 4;
	comp->st->pix->no_size = i;
	comp->st->pix->no = (int *)ft_calloc(sizeof(int),
			i);
	while (size > 0)
	{
		a = comp->no->pixels[--size] & 0xff;
		b = comp->no->pixels[--size] & 0xff;
		g = comp->no->pixels[--size] & 0xff;
		r = comp->no->pixels[--size] & 0xff;
		comp->st->pix->no[--i] = (r << 24) | (g << 16) | (b << 8) | a;
	}
}

static void	save_south_colors(t_compass *comp, int i, int size)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = 0;
	g = 0;
	b = 0;
	a = 0;
	size = i * 4;
	comp->st->pix->so_size = i;
	comp->st->pix->so = (int *)ft_calloc(sizeof(int),
			i);
	while (size > 0)
	{
		a = comp->so->pixels[--size] & 0xff;
		b = comp->so->pixels[--size] & 0xff;
		g = comp->so->pixels[--size] & 0xff;
		r = comp->so->pixels[--size] & 0xff;
		comp->st->pix->so[--i] = (r << 24) | (g << 16) | (b << 8) | a;
	}
}

static void	save_west_colors(t_compass *comp, int i, int size)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = 0;
	g = 0;
	b = 0;
	a = 0;
	size = i * 4;
	comp->st->pix->we_size = i;
	comp->st->pix->we = (int *)ft_calloc(sizeof(int),
			i);
	while (size > 0)
	{
		a = comp->we->pixels[--size] & 0xff;
		b = comp->we->pixels[--size] & 0xff;
		g = comp->we->pixels[--size] & 0xff;
		r = comp->we->pixels[--size] & 0xff;
		comp->st->pix->we[--i] = (r << 24) | (g << 16) | (b << 8) | a;
	}
}

static void	save_east_colors(t_compass *comp, int i, int size)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = 0;
	g = 0;
	b = 0;
	a = 0;
	size = i * 4;
	comp->st->pix->ea_size = i;
	comp->st->pix->ea = (int *)ft_calloc(sizeof(int),
			i);
	while (size > 0)
	{
		a = comp->ea->pixels[--size] & 0xff;
		b = comp->ea->pixels[--size] & 0xff;
		g = comp->ea->pixels[--size] & 0xff;
		r = comp->ea->pixels[--size] & 0xff;
		comp->st->pix->ea[--i] = (r << 24) | (g << 16) | (b << 8) | a;
	}
}

void	save_compass_colors(t_compass *comp)
{
	save_north_colors(comp, comp->no->height * comp->no->width, 0);
	save_south_colors(comp, comp->so->height * comp->so->width, 0);
	save_west_colors(comp, comp->we->height * comp->we->width, 0);
	save_east_colors(comp, comp->ea->height * comp->ea->width, 0);
}
