#include "cube3d.h"

void	free_north(t_compass *comp)
{
	mlx_delete_image(comp->mlx, comp->no);
	mlx_delete_texture(comp->no_text);
	free(comp->no_path);
}

void	free_south(t_compass *comp)
{
	mlx_delete_image(comp->mlx, comp->so);
	mlx_delete_texture(comp->so_text);
	free(comp->so_path);
}

void	free_west(t_compass *comp)
{
	mlx_delete_image(comp->mlx, comp->we);
	mlx_delete_texture(comp->we_text);
	free(comp->we_path);
}

void	free_east(t_compass *comp)
{
	mlx_delete_image(comp->mlx, comp->ea);
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
	mlx_delete_image(comp->mlx, comp->bg);
	free_split(comp);
}
