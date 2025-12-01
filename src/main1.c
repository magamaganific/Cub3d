#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../include/cube3d.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define WIDTH 900
#define HEIGHT 900

// static void error(void)
// {
// 	puts(mlx_error(mlx_errno));
// 	exit(EXIT_FAILURE);
// }
// static void ft_close(void *param)
// {
// }

// int32_t main(void)
// {
// 	mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
// 	if (!mlx)
// 		error();
// 	mlx_texture_t *texture = mlx_load_png("textures/duck.png");
// 	if (!texture)
// 		error();
	
// 	mlx_image_t *img = mlx_texture_to_image(mlx, texture);
// 	if(!img)
// 		error();

// 	mlx_image_to_window(mlx, img, 0, 0);
// 	mlx_delete_image(mlx, img);
// 	mlx_delete_texture(texture);
// 	mlx_terminate(mlx);
// }