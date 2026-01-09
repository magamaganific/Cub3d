/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:43:35 by mfornovi          #+#    #+#             */
/*   Updated: 2025/12/03 14:43:40 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <stdlib.h>
# include <limits.h>
# define WIDTH 900
# define HEIGHT 900
# define BUFFER 100000
# define MINI 30

typedef struct s_compass
{
	mlx_t			*mlx;
	mlx_texture_t	*no_text;
	mlx_texture_t	*so_text;
	mlx_texture_t	*we_text;
	mlx_texture_t	*ea_text;
	mlx_image_t		*no;
	mlx_image_t		*so;
	mlx_image_t		*we;
	mlx_image_t		*ea;
	mlx_image_t		*bg;
	mlx_image_t		*map;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	char			**map_arr;
	int				map_size;
	int				f;
	int				c;
	int				map_width;
	int				map_height;
	int				player_x;
	int				player_y;
}	t_compass;

//	LIBFT
size_t	ft_strlen(const char *c);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *nptr);

//	POSSIBLE FALLS
bool	north_fall(char **map, int x, int y);
bool	south_fall(char **map, int x, int y, t_compass *comp);
bool	west_fall(char **map, int x, int y);
bool	east_fall(char **map, int x, int y, t_compass *comp);
bool	player_may_fall(char **map, int x, int y, t_compass *comp);

//	ASSIGN COMPASS TEXTURES
bool	fill_north(char *buff, int *i, t_compass *comp);
bool	fill_south(char *buff, int *i, t_compass *comp);
bool	fill_west(char *buff, int *i, t_compass *comp);
bool	fill_east(char *buff, int *i, t_compass *comp);

//	ASSIGN BACKGROUND
int		save_color(char *buff, int *i);
bool	fill_f(char *buff, int *i, t_compass *comp);
bool	fill_c(char *buff, int *i, t_compass *comp);
void	set_bg(void *param);

// 	GET MAP LINES
bool	only_spaces_in_line(char *buff, int *i);
char	*save_line(char *buff, int *i);
int		count_nls(char *buff, int n);
char	**split_by_nl(char *buff, int *i, t_compass *comp);

//	FILL COMPASS
bool	invalid_content(char *buff, int i);
bool	fill_selected(char *buff, int *i, t_compass *comp);
bool	compass_full(t_compass *comp);
bool	fill_compass(char *buff, int *i, t_compass *comp);

//	ERRORS
void	print_accepted_input(void);
void	wrong_format(void);
bool	check_map(char *buff, int n);
void	error(void);

//	MAIN UTILS
void	delete_compass(t_compass *comp);
bool	valid_file(char *file_name);
void	free_split(t_compass *comp);
void	init_compass(t_compass *comp);
void	print_map(char **map);

// 	FREE COMPASS
void	free_north(t_compass *comp);
void	free_south(t_compass *comp);
void	free_west(t_compass *comp);
void	free_east(t_compass *comp);
void	free_comp(t_compass *comp);

#endif