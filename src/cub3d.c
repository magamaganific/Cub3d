/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:09:44 by frlorenz          #+#    #+#             */
/*   Updated: 2025/12/05 12:50:29 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static void ft_hook(void* param)
{
	const t_game* game = param;
	int x;
	int y;

	mlx_resize_image(game->back, game->mlx->width, game->mlx->height);
	x = 0;
	while (x < game->mlx->width)
	{
		y = 0;
		while (y < (game->mlx->height / 2))
		{
			mlx_put_pixel(game->back, x, y, 0x33CCFFFF);
			y++;
		}
		while (y < game->mlx->height)
		{
			mlx_put_pixel(game->back, x, y, 0x006600FF);
			y++;
		}
		x++;
	}
}

int	main(int argc, char **argv)
{
	(void) argv;
	t_game	*game;

	
	if(argc == 2)
	{
		game = (t_game*) malloc (sizeof(t_game *));
		if (!game)
			return(0);
		
		game->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
		if (!game->mlx)
			ft_error();
		game->back = mlx_new_image(game->mlx, WIDTH, HEIGHT);
		if (!game->back || (mlx_image_to_window(game->mlx, game->back, 0, 0) < 0))
			ft_error();
		game->front = mlx_texture_to_image(game->mlx, mlx_load_png("/home/frlorenz/42_cursus/vault/cub3d/textures/Box.png"));
		if (!game->front || (mlx_image_to_window(game->mlx, game->front, 0, 0) < 0))
			ft_error();
		mlx_loop_hook(game->mlx, ft_hook, game);
		mlx_loop(game->mlx);
		mlx_terminate(game->mlx);
	}
	else
		printf("Error\n Numero de arguentos incorrecto");
	return (0);
}