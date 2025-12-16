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

void	free_split(t_compass *comp)
{
	int	i;

	i = 0;
	while (i < comp->map_size)
	{
		free(comp->map_arr[i]);
		i++;
	}
	free(comp->map_arr);
}

void	init_compass(t_compass *comp)
{
	comp->f = 0;
	comp->c = 0;
	comp->map_height = 0;
	comp->map_width = 0;
	comp->player_x = 0;
	comp->player_y = 0;
	comp->no_path = NULL;
	comp->so_path = NULL;
	comp->we_path = NULL;
	comp->ea_path = NULL;
}

void	free_comp(t_compass *comp)
{
	mlx_delete_image(comp->mlx, comp->bg);
	mlx_delete_image(comp->mlx, comp->no);
	mlx_delete_image(comp->mlx, comp->so);
	mlx_delete_image(comp->mlx, comp->we);
	mlx_delete_image(comp->mlx, comp->ea);
	mlx_delete_texture(comp->no_text);
	mlx_delete_texture(comp->so_text);
	mlx_delete_texture(comp->we_text);
	mlx_delete_texture(comp->ea_text);
	free(comp->no_path);
	free(comp->so_path);
	free(comp->we_path);
	free(comp->ea_path);
	free_split(comp);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}
