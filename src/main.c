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
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#define WIDTH 900
#define HEIGHT 900

void	print_accepted_input(void)
{
	printf("Accepted input: \n	./Game [MAP PATH]\n");
	printf("		(maps available in the \"maps\" directory)\n");
}

void	wrong_format(void)
{
	printf("Make sure your .cub has valid contents\n");
}

bool	valid_file(char *file_name)
{
	int	i;

	i = -1;
	while (file_name[++i]);
	if (file_name[i - 4] != '.' || file_name[i - 3] != 'c'
			|| file_name[i - 2] != 'u' || file_name[i - 1] != 'b')
			return (false);
	return (true);
}

// bool	parse_input(int fd, t_compass *comp)
// {

// }

int	main(int ac, char **av)
{
	int	fd;
	t_compass comp;

	comp.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	fd = open(av[1], O_RDONLY);
	if (ac != 2 || !valid_file(av[1]) || fd == -1)
	{
		print_accepted_input();
		if (fd == -1)
			return (-1);
		return (close(fd), -1);
	}
	// if (!parse_input(fd, &comp))
	// 	return (wrong_format(), close(fd), -1);
	mlx_loop(comp.mlx);
	mlx_terminate(comp.mlx);
	close(fd);
}
