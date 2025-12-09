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
#define BUFFER 715827882

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

	i = 0;
	while (file_name[i])
		i++;
	if (file_name[i - 4] != '.' || file_name[i - 3] != 'c'
		|| file_name[i - 2] != 'u' || file_name[i - 1] != 'b')
		return (false);
	return (true);
}

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

bool	invalid_content(char *buff, int i)
{
	if ((buff[i] == 'N' && buff[i] == 'O')
		|| (buff[i] == 'S' && buff[i] == 'O')
		|| (buff[i] == 'W' && buff[i] == 'E')
		|| (buff[i] == 'E' && buff[i] == 'A')
		|| buff[i] == 'F' || buff[i] == 'C')
		return (false);
	return (true);
}

bool	fill_north(char *buff, int *i, t_compass *comp)
{
	int		start;
	int		n;

	if (!(!comp->no_path))
		return (false);
	*i = *i + 2;
	n = -1;
	while (buff[*i] == '	' || buff[*i] == ' '
		|| buff[*i] == '\n')
		*i++;
	start = *i;
	while (buff[*i] != '\n')
		*i++;
	comp->no_path = malloc((*i - start) * sizeof(char));
	while (start < *i)
	{
		comp->no_path[++n] = buff[start];
		start++;
	}
	comp->no_text = mlx_load_png(comp->no_path);
	if (!comp->no_text)
		return(error(), false);
	comp->no = mlx_texture_to_image(comp->mlx, comp->no_text);
	if (!comp->no)
		return(error(), false);
}

bool	fill_south(char *buff, int *i, t_compass *comp)
{
	int		start;
	int		n;

	if (!(!comp->so_path))
		return (false);
	*i = *i + 2;
	n = -1;
	while (buff[*i] == '	' || buff[*i] == ' '
		|| buff[*i] == '\n')
		*i++;
	start = *i;
	while (buff[*i] != '\n')
		*i++;
	comp->so_path = malloc((*i - start) * sizeof(char));
	while (start < *i)
	{
		comp->so_path[++n] = buff[start];
		start++;
	}
	comp->so_text = mlx_load_png(comp->so_path);
	if (!comp->so_text)
		return(error(), false);
	comp->so = mlx_texture_to_image(comp->mlx, comp->so_text);
	if (!comp->so)
		return(error(), false);
}


bool	fill_west(char *buff, int *i, t_compass *comp)
{
	int		start;
	int		n;

	if (!(!comp->we_path))
		return (false);
	*i = *i + 2;
	n = -1;
	while (buff[*i] == '	' || buff[*i] == ' '
		|| buff[*i] == '\n')
		*i++;
	start = *i;
	while (buff[*i] != '\n')
		*i++;
	comp->we_path = malloc((*i - start) * sizeof(char));
	while (start < *i)
	{
		comp->we_path[++n] = buff[start];
		start++;
	}
	comp->we_text = mlx_load_png(comp->we_path);
	if (!comp->we_text)
		return(error(), false);
	comp->we = mlx_texture_to_image(comp->mlx, comp->we_text);
	if (!comp->we)
		return(error(), false);
}

bool	fill_east(char *buff, int *i, t_compass *comp)
{
	int		start;
	int		n;

	if (!(!comp->ea_path))
		return (false);
	*i = *i + 2;
	n = -1;
	while (buff[*i] == '	' || buff[*i] == ' '
		|| buff[*i] == '\n')
		*i++;
	start = *i;
	while (buff[*i] != '\n')
		*i++;
	comp->ea_path = malloc((*i - start) * sizeof(char));
	while (start < *i)
	{
		comp->ea_path[++n] = buff[start];
		start++;
	}
	comp->ea_text = mlx_load_png(comp->ea_path);
	if (!comp->ea_text)
		return(error(), false);
	comp->ea = mlx_texture_to_image(comp->mlx, comp->ea_text);
	if (!comp->ea)
		return(error(), false);
}

bool	fill_F(char *buff, int *i, t_compass *comp)
{
	int		red;
	int		blue;
	int		green;
	char	num[3];
}

bool	fill_selected(char *buff, int *i, t_compass *comp)
{
	if (buff[*i] == 'N' && buff[*i + 1] == 'O')
		return (fill_north(buff, i, comp));
	else if (buff[*i] == 'S' && buff[*i + 1] == 'O')
		return (fill_south(buff, i, comp));
	else if (buff[*i] == 'W' && buff[*i + 1] == 'E')
		return (fill_west(buff, i, comp));
	else if (buff[*i] == 'E' && buff[*i + 1] == 'A')
		return (fill_east(buff, i, comp));
	else if (buff[*i] == 'F')
		return (fill_F(buff, i, comp));
	else if (buff[*i] == 'C')
		return (fill_C(buff, i, comp));
	return (false);
}

bool	fill_compass(char *buff, t_compass *comp)
{
	int	i;

	i = 0;
	while (buff[i])
	{
		while (buff[i] == '	' || buff[i] == ' ' || buff[i] == '\n')
			i++;
		if (invalid_content(buff, i))
			return (false);
		if (!fill_selected(buff, &i, comp))
			return(false);
		if (compass_full(comp))
			break ;
	}
	return(true);
}

bool	parse_input(int fd, t_compass *comp)
{
	// --------------------------las texturas---------------------------
	// comp->no_text = mlx_load_png("./textures/duck.png");
	// if(!comp->no_text)
	// 	error();
	// comp->no = mlx_texture_to_image(comp->mlx, comp->no_text);
	// if (!comp->no)
	// 	error();
	// mlx_image_to_window(comp->mlx, comp->no, 0, 0);
	// return(true);
	// --------------------------las texturas---------------------------
	char	*buff;
	ssize_t	red;

	buff = malloc(BUFFER * sizeof(char));
	red = read(fd, buff, BUFFER);
	if (!red)
		return (false);
	printf("fd:\n%s\n", buff);
	printf("red = %zu\n", red);
	if (!fill_compass(buff, comp))
		return (false);
	free (buff);
	return (true);
}

int	main(int ac, char **av)
{
	int			fd;
	t_compass	comp;

	comp.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	fd = open(av[1], O_RDONLY);
	if (ac != 2 || !valid_file(av[1]) || fd == -1)
	{
		print_accepted_input();
		if (fd == -1)
			return (-1);
		return (close(fd), -1);
	}
	if (!parse_input(fd, &comp))
		return (error(), wrong_format(), close(fd), -1);
	mlx_loop(comp.mlx);
	mlx_terminate(comp.mlx);
	close(fd);
}
