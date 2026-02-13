/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:40:06 by mfornovi          #+#    #+#             */
/*   Updated: 2026/01/09 11:40:08 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	ft_draw_square(int x, int y, int color, mlx_image_t *map)
{
	int	i;

	i = 0;
	while (i <= SQUARE_SIZE)
	{
		mlx_put_pixel(map, x + i, y, color);
		mlx_put_pixel(map, x, y + i, color);
		mlx_put_pixel(map, x + SQUARE_SIZE, y + i, color);
		mlx_put_pixel(map, x + i, y + SQUARE_SIZE, color);
		i++;
	}
}

void	init_player(t_compass *comp)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	comp->raymap = mlx_new_image(comp->mlx, (comp->map_width + 1) * SQUARE_SIZE,
			(comp->map_height + 1) * SQUARE_SIZE);
	if (!comp->raymap)
		error();
	comp->player = mlx_new_image(comp->mlx, PLAYER_SIZE + 1, PLAYER_SIZE + 1);
	if (!comp->player)
		error();
	while (x <= PLAYER_SIZE)
	{
		mlx_put_pixel(comp->player, x, 0, 0xFF0000FF);
		mlx_put_pixel(comp->player, x, PLAYER_SIZE, 0xFF0000FF);
		x++;
	}
	while (y <= PLAYER_SIZE)
	{
		mlx_put_pixel(comp->player, 0, y, 0xFF0000FF);
		mlx_put_pixel(comp->player, PLAYER_SIZE, y, 0xFF0000FF);
		y++;
	}
}

void	draw_minimap(t_compass *comp)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	comp->map = mlx_new_image(comp->mlx, (comp->map_width + 1) * SQUARE_SIZE,
			(comp->map_height + 1) * SQUARE_SIZE);
	if (!comp->map)
		error();
	while (y < comp->map_height)
	{
		x = 0;
		while (comp->map_arr[y][x])
		{
			if (comp->map_arr[y][x] == '1')
				ft_draw_square(x * SQUARE_SIZE, y * SQUARE_SIZE, 0xFF0000FF,
					comp->map);
			x++;
		}
		y++;
	}
	init_player(comp);
}

void	game_to_window(t_compass *comp)
{
	mlx_image_to_window(comp->mlx, comp->bg, 0, 0);
	mlx_image_to_window(comp->mlx, comp->walls, 0, 0);
	mlx_image_to_window(comp->mlx, comp->map, 0, 0);
	mlx_image_to_window(comp->mlx, comp->raymap, 0, 0);
	mlx_image_to_window(comp->mlx, comp->player,
		comp->player_x, comp->player_y);
	comp->player_x += HALF;
	comp->player_y += HALF;
}

void	save_north_colors(t_compass *comp, int i, int size)
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
	comp->sight->pixels->no_pix = (int *)ft_calloc(sizeof(int)
			, i);
	while (size > 0)
	{
		a = comp->no->pixels[--size] & 0xff;
		b = comp->no->pixels[--size] & 0xff;
		g = comp->no->pixels[--size] & 0xff;
		r = comp->no->pixels[--size] & 0xff;
		comp->sight->pixels->no_pix[--i] = (r << 24) | (g << 16) | (b << 8) | a;
	}
	// printf("a-> %d\n", a);
	// printf("b-> %d\n", b);
	// printf("g-> %d\n", g);
	// printf("r-> %d\n", r);
	ft_draw_square(200, 200, comp->sight->pixels->no_pix[1], comp->walls);
	// printf("nocolor-> %x\n", comp->sight->pixels->no_pix[1]);
}

void	save_south_colors(t_compass *comp, int i, int size)
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
	comp->sight->pixels->so_pix = (int *)ft_calloc(sizeof(int)
			, i);
	while (size > 0)
	{
		a = comp->so->pixels[--size] & 0xff;
		b = comp->so->pixels[--size] & 0xff;
		g = comp->so->pixels[--size] & 0xff;
		r = comp->so->pixels[--size] & 0xff;
		comp->sight->pixels->so_pix[--i] = (r << 24) | (g << 16) | (b << 8) | a;
	}
	// printf("a-> %d\n", a);
	// printf("b-> %d\n", b);
	// printf("g-> %d\n", g);
	// printf("r-> %d\n", r);
	ft_draw_square(220, 200, comp->sight->pixels->so_pix[1], comp->walls);
	// printf("socolor-> %x\n", comp->sight->pixels->so_pix[1]);
}

void	save_west_colors(t_compass *comp, int i, int size)
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
	comp->sight->pixels->we_pix = (int *)ft_calloc(sizeof(int)
			, i);
	while (size > 0)
	{
		a = comp->we->pixels[--size] & 0xff;
		b = comp->we->pixels[--size] & 0xff;
		g = comp->we->pixels[--size] & 0xff;
		r = comp->we->pixels[--size] & 0xff;
		comp->sight->pixels->we_pix[--i] = (r << 24) | (g << 16) | (b << 8) | a;
	}
	// printf("a-> %d\n", a);
	// printf("b-> %d\n", b);
	// printf("g-> %d\n", g);
	// printf("r-> %d\n", r);
	ft_draw_square(240, 200, comp->sight->pixels->we_pix[1], comp->walls);
	// printf("wecolor-> %x\n", comp->sight->pixels->we_pix[1]);
}

void	save_east_colors(t_compass *comp, int i, int size)
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
	comp->sight->pixels->ea_pix = (int *)ft_calloc(sizeof(int)
			, i);
	while (size > 0)
	{
		a = comp->ea->pixels[--size] & 0xff;
		b = comp->ea->pixels[--size] & 0xff;
		g = comp->ea->pixels[--size] & 0xff;
		r = comp->ea->pixels[--size] & 0xff;
		comp->sight->pixels->ea_pix[--i] = (r << 24) | (g << 16) | (b << 8) | a;
	}
	// printf("a-> %d\n", a);
	// printf("b-> %d\n", b);
	// printf("g-> %d\n", g);
	// printf("r-> %d\n", r);
	ft_draw_square(260, 200, comp->sight->pixels->ea_pix[1], comp->walls);
	// printf("eacolor-> %x\n", comp->sight->pixels->ea_pix[1]);
}

void	save_compass_colors(t_compass *comp)
{
	save_north_colors(comp, comp->no->height * comp->no->width, 0);
	save_south_colors(comp, comp->so->height * comp->so->width, 0);
	save_west_colors(comp, comp->we->height * comp->we->width, 0);
	save_east_colors(comp, comp->ea->height * comp->ea->width, 0);
}

void	startup_map(t_compass *comp)
{
	comp->bg = mlx_new_image(comp->mlx, WIDTH, HEIGHT);
	if (!comp->bg)
		error();
	comp->no = mlx_texture_to_image(comp->mlx, comp->no_text);
	if (!comp->no)
		error();
	comp->so = mlx_texture_to_image(comp->mlx, comp->so_text);
	if (!comp->so)
		error();
	comp->we = mlx_texture_to_image(comp->mlx, comp->we_text);
	if (!comp->we)
		error();
	comp->ea = mlx_texture_to_image(comp->mlx, comp->ea_text);
	if (!comp->ea)
		error();
	comp->walls = mlx_new_image(comp->mlx, WIDTH, HEIGHT);
	if (!comp->walls)
		error();
	draw_minimap(comp);
	mlx_loop_hook(comp->mlx, set_bg, comp);
	save_compass_colors(comp);
	game_to_window(comp);
	draw_raycaster(comp);
	mlx_loop_hook(comp->mlx, player_hook, comp);
}
