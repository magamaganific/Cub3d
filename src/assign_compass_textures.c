/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_compass_textures.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:43:28 by mfornovi          #+#    #+#             */
/*   Updated: 2025/12/18 12:43:30 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
	return (true);
}
