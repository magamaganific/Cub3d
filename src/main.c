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

char *get_path(char *buf)
{
	int	n;
	int i;
	char *res;

	n = -1;
	i = -1;
	while (buf[++n] != '\n' && buf[n]);
	res = malloc(n * sizeof(char));
	while(++i < n - 1)
		res[i] = buf[i];
	res[i] = 0;
	return(res);
}

bool	set_path_to_struct(mlx_texture_t *tex, char *buf )
{
	int	i;
	char *path;

	i = -1;
	while (buf[++i] == ' ' || buf[i] == '	');
	buf = buf + (i - 1);
	path = get_path(buf);
	if (!tex)
	{
		tex = mlx_load_png(path);
		if (!tex)
			return(false);
		// img = mlx_texture_to_image()
	}
	else
		return (false);
	return (true);
}

bool	fill_structure_bit(char *buf, t_compass *comp)
{
	if (buf[0] == 'N' && buf[1] == 'O' && (buf[2] == ' ' || buf[2] == '	'))
		if (!set_path_to_struct(comp->no, buf + 2))
			return(false);
	if (buf[0] == 'S' && buf[1] == 'O' && (buf[2] == ' ' || buf[2] == '	'))
		if (!set_path_to_struct(comp->so, buf + 2))
			return(false);
	if (buf[0] == 'W' && buf[1] == 'E' && (buf[2] == ' ' || buf[2] == '	'))
		if (!set_path_to_struct(comp->we, buf + 2))
			return(false);
	// if (buf[0] == 'E' && buf[1] == 'A' && (buf[2] == ' ' || buf[2] == '	'))
	// 	if (!set_path_to_struct(comp->ea, buf + 2))
	// 		return(false);
	// if (buf[0] == 'F' && (buf[2] == ' ' || buf[2] == '	'))
	// 	if (!set_rgb_to_struct(comp->f, buf + 2))
	// 		return(false);
	return (true);
}

bool	parse_input(int fd, t_compass *comp)
{
	char	buf[INT_MAX];
	int		i;
	ssize_t	r;

	i = -1;
	r = read(fd, buf, INT_MAX);
	if (!r || r == -1)
		return (false);
	while (++i < r)
	{
		if (buf[i] != ' ' && buf[i] != '	')
		{
			printf("buf + i = %s", buf + i);
			if (!fill_structure_bit(buf + i, comp))
				return(false);
			//setup into structure
			//if structure bit already in use -> return(false)
		}
	}
	return(true);
}

int	main(int ac, char **av)
{
	int	fd;
	t_compass comp;

	fd = open(av[1], O_RDONLY);
	if (ac != 2 || !valid_file(av[1]) || fd == -1)
	{
		print_accepted_input();
		if (fd == -1)
			return (-1);
		return (close(fd), -1);
	}
	if (!parse_input(fd, &comp))
		return (wrong_format(), close(fd), -1);
	close(fd);
}
