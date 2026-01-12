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
}

void	init_compass(t_compass *comp)
{
	comp->f = 0;
	comp->c = 0;
	comp->map_size = 0;
	comp->map_width = 0;
	comp->map_height = 0;
	comp->player_x = 0;
	comp->player_y = 0;
	comp->sight_x = 0;
	comp->sight_y = 0;
	comp->sight.cos = 0;
	comp->sight.sin = 0;
	comp->no_path = NULL;
	comp->so_path = NULL;
	comp->we_path = NULL;
	comp->ea_path = NULL;
	comp->map_arr = NULL;
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
