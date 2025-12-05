/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:36:00 by frlorenz          #+#    #+#             */
/*   Updated: 2025/12/05 12:41:37 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3H_H
# define CUB3H_H

# include <limits.h>
# include <stdbool.h>
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

typedef struct s_game
{
	mlx_t* mlx;
	mlx_image_t	*back;
	mlx_image_t	*front;

}	t_game;

#define WIDTH 1080
#define HEIGHT 1080

//map
int		ft_strlen_gnl(const char *s);
void	*ft_memset_gnl(void *b, int c, size_t len);
void	*ft_calloc_gnl(size_t count, size_t len);
char	*ft_strchr_gnl(const char *s, int c);
char	*ft_strjoin_gnl(char *s1, char *s2);
void	clean_memo(char **stash);
char	*get_next_line(int fd);
t_map	*ft_read_map(char *path);


#endif