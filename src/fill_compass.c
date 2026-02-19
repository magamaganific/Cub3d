/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_compass.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:08:25 by mfornovi          #+#    #+#             */
/*   Updated: 2025/12/16 13:08:28 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

bool	invalid_content(char *buff, int i)
{
	if ((buff[i] == 'N' && buff[i + 1] == 'O')
		|| (buff[i] == 'S' && buff[i + 1] == 'O')
		|| (buff[i] == 'W' && buff[i + 1] == 'E')
		|| (buff[i] == 'E' && buff[i + 1] == 'A')
		|| buff[i] == 'F' || buff[i] == 'C')
		return (false);
	return (true);
}

bool	fill_selected(char *buff, int *i, t_compass *comp)
{
	if (buff[*i] == 'N' && buff[*i + 1] == 'O')
		return (fill_north(buff, i, comp));
	else if (buff[*i] == 'S' && buff[*i + 1] == 'O')
		return (fill_south(buff, i, comp));
	else if (buff[*i] == 'W' && buff[*i + 1] == 'E')
		return (fill_west(buff, i, comp));
	else if (buff[*i] == 'E' && buff[*i + 1] == 'A')
		return (fill_east(buff, i, comp));
	else if (buff[*i] == 'F')
		return (fill_f(buff, i, comp));
	else if (buff[*i] == 'C')
		return (fill_c(buff, i, comp));
	return (false);
}

bool	compass_full(t_compass *comp)
{
	if (!comp->no_path || !comp->so_path
		|| !comp->we_path || !comp->ea_path
		|| comp->f == 0 || comp->c == 0)
		return (false);
	return (true);
}

bool	fill_compass(char *buff, int *i, t_compass *comp)
{
	while (buff[*i])
	{
		while (buff[*i] == '	' || buff[*i] == ' '
			|| buff[*i] == '\n')
			*i = *i + 1;
		if (invalid_content(buff, *i))
			return (false);
		if (!fill_selected(buff, i, comp))
			return (false);
		if (compass_full(comp))
			break ;
	}
	return (true);
}
