/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:41:57 by mfornovi          #+#    #+#             */
/*   Updated: 2025/12/03 11:42:00 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../include/cube3d.h"

void	find_player(t_compass *comp)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < comp->map_height)
	{
		while (x < comp->map_width && comp->map_arr[y][x])
		{
			if (comp->map_arr[y][x] == 'N' || comp->map_arr[y][x] == 'S'
				|| comp->map_arr[y][x] == 'W' || comp->map_arr[y][x] == 'E')
			{
				comp->player_x = x;
				comp->player_y = y;
				break ;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

bool	setup_map(char *buff, int *i, t_compass *comp)
{
	while (only_spaces_in_line(buff, i))
		*i = *i + 1;
	if (!check_map(buff, *i))
		return (false);
	comp->map_size = count_nls(buff, *i);
	comp->map_arr = split_by_nl(buff, i, comp);
	find_player(comp);
	if (player_may_fall(comp->map_arr, comp->player_x, comp->player_y, comp))
	{
		printf("Player fell into the void\n");
		return (false);
	}
	return (true);
}

bool	parse_input(int fd, t_compass *comp)
{
	char	*buff;
	ssize_t	red;
	int		i;

	i = 0;
	buff = ft_calloc(sizeof(char), BUFFER);
	if (!buff)
		return (false);
	red = read(fd, buff, BUFFER);
	if (!red || red == -1)
		return (free(buff), false);
	if (!fill_compass(buff, &i, comp))
		return (free(buff), false);
	if (!setup_map(buff, &i, comp))
		return (free(buff), false);
	print_map(comp->map_arr);
	free(buff);
	return (true);
}

void	ft_draw_square(int x, int y, int color, mlx_image_t *map)
{
	int i;

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

void	draw_minimap(t_compass *comp)
{
	int	x;
	int y;

	x = 0;
	y = 0;
	comp->map = mlx_new_image(comp->mlx, (comp->map_width + 1)* SQUARE_SIZE,
		(comp->map_height + 1)* SQUARE_SIZE);
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
	draw_minimap(comp);
	mlx_loop_hook(comp->mlx, set_bg, comp);
	mlx_image_to_window(comp->mlx, comp->bg, 0, 0);
	mlx_image_to_window(comp->mlx, comp->map, 0, 200);
	mlx_image_to_window(comp->mlx, comp->no, 0, 0);
	mlx_image_to_window(comp->mlx, comp->so, 100, 0);
	mlx_image_to_window(comp->mlx, comp->we, 0, 100);
	mlx_image_to_window(comp->mlx, comp->ea, 100, 100);
}

int	main(int ac, char **av)
{
	int			fd;
	t_compass	comp;

	init_compass(&comp);
	fd = open(av[1], O_RDONLY);
	if (ac != 2 || !valid_file(av[1]) || fd == -1)
	{
		print_accepted_input();
		if (fd == -1)
			return (-1);
		return (close(fd), -1);
	}
	if (!parse_input(fd, &comp))
		return (free_comp(&comp), wrong_format(), close(fd), EXIT_FAILURE);
	close(fd);
	comp.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!comp.mlx)
		return (0);
	startup_map(&comp);
	mlx_loop(comp.mlx);
	free_comp(&comp);
	delete_compass(&comp);
	mlx_terminate(comp.mlx);
	return (EXIT_SUCCESS);
}
