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

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"

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
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	char			**map;
	int				map_size;
	int				f;
	int				c;
}	t_compass;

#endif