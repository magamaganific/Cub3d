/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:36:00 by frlorenz          #+#    #+#             */
/*   Updated: 2025/12/11 18:05:06 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3H_H
# define CUB3H_H

# include <limits.h>
# include <stdbool.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "./MLX42/MLX42.h"

#ifndef BUFFER_SIZE
	#define BUFFER_SIZE 42
#endif

typedef struct s_config
{
	int		**F;
	int		**C;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;

}	t_config;

typedef struct s_map
{
	t_config	*config;
	char		**land;

}	t_map;

typedef struct s_player
{
	float	x;
	float	y;

}	t_player;

typedef struct s_game
{
	mlx_t *mlx;
	mlx_image_t	*back;
	mlx_image_t	*front;
	t_player	player;
	char **map;

}	t_game;

#define WIDTH 1080
#define HEIGHT 1080

#define W 119
#define A 97
#define S 115
#define D 100

#define PI 3.14159265359

//map
int		ft_strlen_gnl(const char *s);
void	*ft_memset_gnl(void *b, int c, size_t len);
void	*ft_calloc_gnl(size_t count, size_t len);
char	*ft_strchr_gnl(const char *s, int c);
char	*ft_strjoin_gnl(char *s1, char *s2);
void	clean_memo(char **stash);
char	*get_next_line(int fd);
t_map	*ft_read_map(char *path);
char 	**ft_get_map(void);
void ft_draw_square(int x, int y, int size, int color, mlx_image_t *front);
void ft_draw_map(t_game *game);


#endif