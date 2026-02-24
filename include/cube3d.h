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
# include "lib/MLX42/include/MLX42/MLX42.h"
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
# define WIDTH 1000
# define HEIGHT 1000
# define P_HEIGHT 450
# define BUFFER 100000
# define SQUARE_SIZE 40
# define PLAYER_SIZE 10
# define HALF PLAYER_SIZE / 2
# define SPEED 2
# define M_PI 3.14159265358979323846
# define R_ITER 2
# define FORWARD 'W'
# define BACKWARDS 'S'
# define LEFT 'A'
# define RIGHT 'D'
# define FOV 0x0000FFFF
# define WLL 0xFF0000FF
# define N 0
# define E 1
# define S 2
# define W 3

typedef struct s_co_pixels
{
	double	angle;
	int		wall_dir;
	int		*no_pix;
	int		*so_pix;
	int		*we_pix;
	int		*ea_pix;
}	t_co_pixels;

typedef struct s_raycaster
{
	double	cos;
	double	sin;
	double	angle;
	double	x;
	double	y;
	double	prev_x;
	double	prev_y;
	t_co_pixels *pixels;
}	t_raycaster;

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
	mlx_image_t		*player;
	mlx_image_t		*raymap;
	mlx_image_t		*walls;
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
	double			player_x;
	double			player_y;
	t_raycaster		*sight;
}	t_compass;


//	TO BE CHANGED

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
void	key_close(void *param);

// 	GET MAP LINES
bool	only_spaces_in_line(char *buff, int *i);
char	*save_line(char *buff, int *i);
int		count_nls(char *buff, int n);
char	**split_by_nl(char *buff, int *i, t_compass *comp);

//	MAP TO SCREEN
void	init_player(t_compass *comp);
void	draw_minimap(t_compass *comp);
void	player_hook(void *param);
void	startup_map(t_compass *comp);

//	MAP SCREEN ASSIST
void	save_compass_colors(t_compass *comp);

//	FILL COMPASS
bool	invalid_content(char *buff, int i);
bool	fill_selected(char *buff, int *i, t_compass *comp);
bool	compass_full(t_compass *comp);
bool	fill_compass(char *buff, int *i, t_compass *comp);

//	PLAYER HOOK
void	player_hook(void *param);

//	RAYCAST FUNCTS
void	clear_image(mlx_image_t *image);
double	degree_to_radians(double	degree);
void	draw_raycaster(t_compass *comp);

//	RAYCAST ASSISTANTS
bool	coordenate_collides(t_compass *comp, double fx, double fy);
bool	ray_collides(t_compass *comp, double x, double y);
bool	corner_collide(t_compass *comp, double x, double y);
double	degree_to_radians(double degree);
void	save_angle_data(t_compass *comp, double *angle);
void	reset_line_to_player(t_compass *comp, double angle);

//	ERRORS
void	print_accepted_input(void);
void	wrong_format(void);
bool	check_map(char *buff, int n);
void	error(void);

//	MAIN UTILS
void	delete_compass(t_compass *comp);
bool	valid_file(char *file_name);
void	free_split(char **arr, int size);
void	init_compass(t_compass *comp);
void	print_map(char **map);

// 	FREE COMPASS
void	free_north(t_compass *comp);
void	free_south(t_compass *comp);
void	free_west(t_compass *comp);
void	free_east(t_compass *comp);
void	free_comp(t_compass *comp);

#endif