/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:08:52 by mfornovi          #+#    #+#             */
/*   Updated: 2025/12/16 13:08:54 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

void	free_split(char **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	delete_compass(t_compass *comp)
{
	if (comp->no)
		mlx_delete_image(comp->mlx, comp->no);
	if (comp->so)
		mlx_delete_image(comp->mlx, comp->so);
	if (comp->we)
		mlx_delete_image(comp->mlx, comp->we);
	if (comp->ea)
		mlx_delete_image(comp->mlx, comp->ea);
	if (comp->bg)
		mlx_delete_image(comp->mlx, comp->bg);
	if (comp->map)
		mlx_delete_image(comp->mlx, comp->map);
	if (comp->raymap)
		mlx_delete_image(comp->mlx, comp->raymap);
	if (comp->walls)
		mlx_delete_image(comp->mlx, comp->raymap);
}

void	init_comp_arrays(t_compass *comp)
{
	comp->no_path = NULL;
	comp->so_path = NULL;
	comp->we_path = NULL;
	comp->ea_path = NULL;
	comp->map_arr = NULL;
	comp->sight->pixels->no_pix = NULL;
	comp->sight->pixels->so_pix = NULL;
	comp->sight->pixels->we_pix = NULL;
	comp->sight->pixels->ea_pix = NULL;
}

void	init_compass(t_compass *comp)
{
	comp->sight = (t_raycaster *) malloc(sizeof(t_raycaster));
	if (!comp->sight)
		exit(EXIT_FAILURE);
	comp->sight->pixels = (t_co_pixels *) malloc(sizeof(t_co_pixels));
	if (!comp->sight)
		exit(EXIT_FAILURE);
	comp->f = 0;
	comp->c = 0;
	comp->map_size = 0;
	comp->map_width = 0;
	comp->map_height = 0;
	comp->player_x = 0;
	comp->player_y = 0;
	comp->sight->x = 0;
	comp->sight->y = 0;
	comp->sight->prev_x = 0;
	comp->sight->prev_y = 0;
	comp->sight->cos = 0;
	comp->sight->sin = 0;
	comp->sight->angle = 0;
	comp->sight->pixels->wall_dir = 0;
	init_comp_arrays(comp);
}
