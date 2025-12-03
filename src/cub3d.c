/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:09:44 by frlorenz          #+#    #+#             */
/*   Updated: 2025/12/03 09:56:32 by frlorenz         ###   ########.fr       */
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
	const mlx_t* mlx = param;

	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

int	main(int argc, char **argv)
{
	t_map *map;
	if(argc == 2)
	{
		map = ft_read_map(argv[1]);
		mlx_set_setting(MLX_MAXIMIZED, true);
		mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
		if (!mlx)
			ft_error();
		mlx_image_t* img = mlx_new_image(mlx, 256, 256);
		if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
			ft_error();
		mlx_put_pixel(img, 0, 0, 0xFF0000FF);
		mlx_loop_hook(mlx, ft_hook, mlx);
		mlx_loop(mlx);
		mlx_terminate(mlx);
	}
	else
		printf("Error\n Numero de arguentos incorrecto");
	return (0);
}