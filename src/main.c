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

void	init_compass(t_compass *comp)
{
	comp->no->enabled = false;
	comp->so->enabled = false;
	comp->we->enabled = false;
	comp->ea->enabled = false;
	comp->f = -1;
	comp->c = -1;
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

bool	set_path_to_struct(mlx_image_t *img, char *buf )
{
	int	i;

	i = -1;
	while (buf[++i] == ' ' || buf[i] == '	');
	buf = buf + (i - 1);

	img = mlx_load_png(buf);
}

bool	fill_structure_bit(char *buf, t_compass *comp)
{
	int	i;

	if (buf[0] == 'N' && buf[1] == 'O' && (buf[2] == ' ' || buf[2] == '	'))
		if (!set_path_to_struct(comp->no, buf + 2))
			return(false);
	if (buf[0] == 'S' && buf[1] == 'O' && (buf[2] == ' ' || buf[2] == '	'))
		if (!set_path_to_struct(comp->so, buf + 2))
			return(false);
	if (buf[0] == 'W' && buf[1] == 'E' && (buf[2] == ' ' || buf[2] == '	'))
		if (!set_path_to_struct(comp->we, buf + 2))
			return(false);
	if (buf[0] == 'E' && buf[1] == 'A' && (buf[2] == ' ' || buf[2] == '	'))
		if (!set_path_to_struct(comp->ea, buf + 2))
			return(false);
	if (buf[0] == 'F' && (buf[2] == ' ' || buf[2] == '	'))
		if (!set_rgb_to_struct(comp->f, buf + 2))
			return(false);
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
	while (i < r)
	{
		if (buf[i] != ' ' && buf[i] != '	')
		{
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
		return (wrong_format(), close(fd), -1);
	close(fd);
}
