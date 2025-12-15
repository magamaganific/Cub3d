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

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*dst;
	size_t			p;

	p = 0;
	dst = (unsigned char *) s;
	while (p < n)
	{
		dst[p] = '\0';
		p++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*memory;

	memory = malloc (size * nmemb);
	if (!memory)
		return (NULL);
	ft_bzero(memory, size * nmemb);
	return (memory);
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int	ft_atoi(const char *nptr)
{
	int	sgn;
	int	dig;
	int	num;

	sgn = 1;
	dig = 0;
	num = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sgn = -sgn;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		dig = *nptr - '0';
		num = num * 10 + dig;
		nptr++;
	}
	num = num * sgn;
	return (num);
}

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
	if ((buff[i] == 'N' && buff[i + 1] == 'O')
		|| (buff[i] == 'S' && buff[i + 1] == 'O')
		|| (buff[i] == 'W' && buff[i + 1] == 'E')
		|| (buff[i] == 'E' && buff[i + 1] == 'A')
		|| buff[i] == 'F' || buff[i] == 'C')
		return (false);
	return (true);
}

bool	fill_north(char *buff, int *i, t_compass *comp)
{
	int		start;
	int		n;

	if (comp->no_path != NULL)
		return (false);
	*i = *i + 2;
	n = -1;
	while (buff[*i] == '	' || buff[*i] == ' ')
		*i = *i + 1;
	start = *i;
	while (buff[*i] != '\n')
		*i = *i + 1;
	comp->no_path = ft_calloc(sizeof(char),*i - start + 1);
	if (!comp->no_path)
		return (false);
	while (start <= *i)
		comp->no_path[++n] = buff[start++];
	comp->no_path[n] = 0;
	comp->no_text = mlx_load_png(comp->no_path);
	if (!comp->no_text)
		return (error(), false);
	comp->no = mlx_texture_to_image(comp->mlx, comp->no_text);
	if (!comp->no)
		return (error(), false);
	return (true);
}

bool	fill_south(char *buff, int *i, t_compass *comp)
{
	int		start;
	int		n;

	if (comp->so_path != NULL)
		return (false);
	*i = *i + 2;
	n = -1;
	while (buff[*i] == '	' || buff[*i] == ' ')
		*i = *i + 1;
	start = *i;
	while (buff[*i] != '\n')
		*i = *i + 1;
	comp->so_path = ft_calloc(sizeof(char),*i - start + 1);
	if (!comp->so_path)
		return (false);
	while (start <= *i)
		comp->so_path[++n] = buff[start++];
	comp->so_path[n] = 0;
	comp->so_text = mlx_load_png(comp->so_path);
	if (!comp->so_text)
		return (error(), false);
	comp->so = mlx_texture_to_image(comp->mlx, comp->so_text);
	if (!comp->so)
		return (error(), false);
	return (true);
}


bool	fill_west(char *buff, int *i, t_compass *comp)
{
	int		start;
	int		n;

	if (comp->we_path != NULL)
		return (false);
	*i = *i + 2;
	n = -1;
	while (buff[*i] == '	' || buff[*i] == ' ')
		*i = *i + 1;
	start = *i;
	while (buff[*i] != '\n')
		*i = *i + 1;
	comp->we_path = ft_calloc(sizeof(char),*i - start + 1);
	if (!comp->we_path)
		return (false);
	while (start <= *i)
		comp->we_path[++n] = buff[start++];
	comp->we_path[n] = 0;
	comp->we_text = mlx_load_png(comp->we_path);
	if (!comp->we_text)
		return (error(), false);
	comp->we = mlx_texture_to_image(comp->mlx, comp->we_text);
	if (!comp->we)
		return (error(), false);
	return (true);
}

bool	fill_east(char *buff, int *i, t_compass *comp)
{
	int		start;
	int		n;

	if (comp->ea_path != NULL)
		return (false);
	*i = *i + 2;
	n = -1;
	while (buff[*i] == '	' || buff[*i] == ' ')
		*i = *i + 1;
	start = *i;
	while (buff[*i] != '\n')
		*i = *i + 1;
	comp->ea_path = ft_calloc(sizeof(char),*i - start + 1);
	if (!comp->ea_path)
		return (false);
	while (start <= *i)
		comp->ea_path[++n] = buff[start++];
	comp->ea_path[n] = 0;
	comp->ea_text = mlx_load_png(comp->ea_path);
	if (!comp->ea_text)
		return (error(), false);
	comp->ea = mlx_texture_to_image(comp->mlx, comp->ea_text);
	if (!comp->ea)
		return (error(), false);
	return (true);
}

int	save_color(char *buff, int *i)
{
	int		color;
	int		start;
	int		n;
	char	*num;

	start = *i;
	n = -1;
	while (buff[*i] >= '0' && buff[*i] <= '9')
		*i = *i + 1;
	if (*i - start > 4 || *i == start)
		return (-1);
	num = ft_calloc(sizeof(char),*i - start + 1);
	if (!num)
		return (-1);
	while (start <= *i)
		num[++n] = buff[start++];
	num[n] = 0;
	color = ft_atoi(num);
	*i = *i + 1;
	free(num);
	return (color & 0xff);
}

bool	fill_F(char *buff, int *i, t_compass *comp)
{
	int		red;
	int		blue;
	int		green;

	comp->f = 0;
	*i = *i + 1;
	while (buff[*i] == '	' || buff[*i] == ' ')
		*i = *i + 1;
	red = save_color(buff, i);
	if (red == -1)
		return (false);
	blue = save_color(buff, i);
	if (blue == -1)
		return (false);
	green = save_color(buff, i);
	if (green == -1)
		return (false);
	comp->f = (red << 24) | (green << 16) | (blue << 8) | 255;
	return (true);
}


bool	fill_C(char *buff, int *i, t_compass *comp)
{
	int		red;
	int		blue;
	int		green;

	comp->c = 0;
	*i = *i + 1;
	while (buff[*i] == '	' || buff[*i] == ' ')
		*i = *i + 1;
	red = save_color(buff, i);
	if (red == -1)
		return (false);
	green = save_color(buff, i);
	if (green == -1)
		return (false);
	blue = save_color(buff, i);
	if (blue == -1)
		return (false);
	comp->c = (red << 24) | (green << 16) | (blue << 8) | 255;
	return (true);
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

bool	compass_full(t_compass *comp)
{
	if (!comp->no_path || !comp->so_path
		|| !comp->we_path || !comp->ea_path
		|| comp->f == 0 || comp->c == 0)
		return (false);
	return (true);
}

bool	fill_compass(char *buff, int *i, t_compass *comp)
{
	while (buff[*i])
	{
		while (buff[*i] == '	' || buff[*i] == ' '
			|| buff[*i] == '\n')
			*i = *i + 1;
		if (invalid_content(buff, *i))
			return (false);
		if (!fill_selected(buff, i, comp))
			return (false);
		if (compass_full(comp))
			break ;
	}
	return (true);
}

static void	set_bg(void *param)
{
	const t_compass* comp;
	int	x;
	int	y;

	comp = (t_compass *)param;
	mlx_resize_image(comp->bg, comp->mlx->width, comp->mlx->height);
	x = 0;
	while (x < comp->mlx->width)
	{
		y = 0;
		while (y < (comp->mlx->height / 2))
		{
			mlx_put_pixel(comp->bg, x, y, comp->f);
			y++;
		}
		while (y < comp->mlx->height)
		{
			mlx_put_pixel(comp->bg, x, y, comp->c);
			y++;
		}
		x++;
	}
}

bool	only_spaces_in_line(char *buff, int *i)
{
	int n;

	n = *i;
	while (buff[n] != '\n')
	{
		if (buff[n] != '	' && buff[n] != ' ')
			return(false);
		n++;
	}
	return (true);
}

bool	check_map(char *buff, int n)
{
	int	player;

	player = 0;
	while(buff[n])
	{
		if (!(buff[n] != '1' || buff[n] != '0' || buff[n] != '\n'
			|| buff[n] != 'N' || buff[n] != 'S' || buff[n] != 'W'
			|| buff[n] != 'E' || buff[n] != ' '))
			return(false);
		if (buff[n] == 'N' || buff[n] == 'S' || buff[n] == 'W'
			|| buff[n] == 'E')
		{
			if (player == 1)
				return(printf("More than one player\n"),false);
			player = 1;
		}
		n++;
	}
	if (!player)
		return(printf("Player mising\n"), false);
	return (true);
}

char	*save_line(char *buff, int *i)
{
	char	*line;
	int		size;
	int		n;
	int		j;

	n = *i;
	j = 0;
	while (buff[n] && buff[n] != '\n')
		n++;
	size = n - *i;
	line = ft_calloc(sizeof(char), size + 1);
	while (j < size)
	{
		line[j] = buff[*i];
		*i = *i + 1;
		j++;
	}
	line[j] = 0;
	*i = *i + 1;
	return (line);
}

int	count_nls(char *buff, int n)
{
	int	nls;

	nls = 1;
	while (buff[n])
	{
		if (buff[n] == '\n')
			nls++;
		n++;
	}
	return(nls);
}

char	**split_by_nl(char *buff, int *i)
{
	char	**split;
	int		size;
	int		n;

	n = 0;
	size = count_nls(buff, *i);
	printf("size-> %d\n", size);
	split = (char **)ft_calloc(sizeof(char *), size + 1);
	while (n < size)
	{
		split[n] = save_line(buff, i);
		n++;
	}
	split[n] = NULL;
	printf("split complete\n");
	return(split);
}

bool	setup_map(char *buff, int *i, t_compass *comp)
{
	while (only_spaces_in_line(buff, i))
		*i = *i + 1;
	if (!check_map(buff, *i))
		return (false);
	comp->map_size = count_nls(buff, *i);
	comp->map = split_by_nl(buff, i);
	return((true));
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while(map[i])
	{
		printf("line[%d]-> %s\n", i, map[i]);
		i++;
	}
}

bool	parse_input(int fd, t_compass *comp)
{
	char	*buff;
	ssize_t	red;
	int		i;

	i = 0;
	buff = ft_calloc(sizeof(char), BUFFER);
	if (!buff)
		return(false);
	red = read(fd, buff, BUFFER);
	if (!red || red == -1)
		return (free(buff), false);
	if (!fill_compass(buff, &i, comp))
		return (free(buff), false);
	if(!setup_map(buff, &i, comp))
		return (free(buff), false);
	print_map(comp->map);
	comp->bg = mlx_new_image(comp->mlx, WIDTH, HEIGHT);
	mlx_loop_hook(comp->mlx, set_bg, comp);
	free(buff);
	mlx_image_to_window(comp->mlx, comp->bg, 0, 0);
	mlx_image_to_window(comp->mlx, comp->no, 0, 0);
	mlx_image_to_window(comp->mlx, comp->so, 100, 0);
	mlx_image_to_window(comp->mlx, comp->we, 0, 100);
	mlx_image_to_window(comp->mlx, comp->ea, 100, 100);
	return (true);
}
void	init_compass(t_compass *comp)
{
	comp->f = 0;
	comp->c = 0;
	comp->no_path = NULL;
	comp->so_path = NULL;
	comp->we_path = NULL;
	comp->ea_path = NULL;
}

void	free_split(t_compass *comp)
{
	int	i;

	i = 0;
	while(i < comp->map_size)
	{
		printf("free\n");
		free(comp->map[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	int			fd;
	t_compass	comp;

	init_compass(&comp);
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
	free_split(&comp);
	mlx_terminate(comp.mlx);
	close(fd);
}
