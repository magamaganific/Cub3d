#include "MLX42/include/MLX42/MLX42.h"

typedef struct s_vars{
	void	*mlx;
	void	*win;
}	t_vars;

int close(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

typedef struct s_data{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel /8));
	*(unsigned int*)dst = color;
}

int main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	// t_vars	vars;
	char	*relative_path = "Duck.xpm";
	int img_width;
	int img_height;

	mlx = mlx_init();
	img.img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
	// vars.mlx = mlx_init();
	// vars.win =  mlx_new_window(vars.mlx, 1920, 1080, "Hello World!");
	// mlx_hook(vars.win, 2, 1L<<0, close, &vars);
	// mlx_loop(vars.mlx);
	// mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello World!");
	// img.img = mlx_new_image(mlx, 1920, 1080);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	// for (int i = 0; i < 1920 ; i++)
	// 	my_mlx_pixel_put(&img, i, 540, 0x00FF0000);
	for (int i = 0;  i < 1920 - 99; i = i + 99)
	{
		mlx_put_image_to_window(mlx, mlx_win, img.img, i, 0);
	}
	mlx_loop(mlx);
}