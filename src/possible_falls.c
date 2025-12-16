/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   possible_falls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:09:04 by mfornovi          #+#    #+#             */
/*   Updated: 2025/12/16 13:09:06 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	north_fall(char **map, int x, int y)
{
	if (y - 1 < 0)
		return (true);
	if (map[y - 1][x] == ' ')
		return (true);
	return (false);
}

bool	south_fall(char **map, int x, int y, t_compass *comp)
{
	if (y + 1 > comp->map_height)
		return (true);
	if (map[y + 1][x] == ' ')
		return (true);
	return (false);
}

bool	west_fall(char **map, int x, int y)
{
	if (x - 1 < 0)
		return (true);
	if (map[y][x - 1] == ' ')
		return (true);
	return (false);
}

bool	east_fall(char **map, int x, int y, t_compass *comp)
{
	if (x + 1 > comp->map_width)
		return (true);
	if (map[y][x + 1] == ' ')
		return (true);
	return (false);
}

bool	player_may_fall(char **map, int x, int y, t_compass *comp)
{
	if (x > comp->map_width || y > comp->map_height || x < 0 || y < 0)
		return (false);
	if (map[y][x] != '-' && map[y][x] != '1')
	{
		map[y][x] = '-';
		if (north_fall(map, x, y) || south_fall(map, x, y, comp)
			|| west_fall(map, x, y) || east_fall(map, x, y, comp))
			return (true);
		else if (player_may_fall(map, x + 1, y, comp))
			return (true);
		else if (player_may_fall(map, x - 1, y, comp))
			return (true);
		else if (player_may_fall(map, x, y + 1, comp))
			return (true);
		else if (player_may_fall(map, x, y - 1, comp))
			return (true);
	}
	return (false);
}
