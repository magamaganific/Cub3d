/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_compass.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:43:38 by mfornovi          #+#    #+#             */
/*   Updated: 2025/12/18 12:43:41 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_north(t_compass *comp)
{
	if (comp->no_text)
		mlx_delete_texture(comp->no_text);
	free(comp->no_path);
}

void	free_south(t_compass *comp)
{
	if (comp->so_text)
		mlx_delete_texture(comp->so_text);
	free(comp->so_path);
}

void	free_west(t_compass *comp)
{
	if (comp->we_text)
		mlx_delete_texture(comp->we_text);
	free(comp->we_path);
}

void	free_east(t_compass *comp)
{
	if (comp->ea_text)
		mlx_delete_texture(comp->ea_text);
	free(comp->ea_path);
}

void	free_comp(t_compass *comp)
{
	if (comp->no_path != NULL)
		free_north(comp);
	if (comp->so_path != NULL)
		free_south(comp);
	if (comp->we_path != NULL)
		free_west(comp);
	if (comp->ea_path != NULL)
		free_east(comp);
	if (comp->st->pix->no != NULL)
		free(comp->st->pix->no);
	if (comp->st->pix->so != NULL)
		free(comp->st->pix->so);
	if (comp->st->pix->we != NULL)
		free(comp->st->pix->we);
	if (comp->st->pix->ea != NULL)
		free(comp->st->pix->ea);
	if (comp->st->pix != NULL)
		free(comp->st->pix);
	if (comp->st != NULL)
		free(comp->st);
	free_split(comp->map_arr, comp->map_size);
}
