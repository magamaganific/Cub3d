/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 19:32:46 by frlorenz          #+#    #+#             */
/*   Updated: 2025/12/03 12:52:50 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



t_map *ft_read_map(char *path)
{
	int		fd;
	char	*line;
	t_map	*map;
	char **land;
	int i;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = (t_map*) malloc(sizeof(t_map*));
	if (!map)
		return (NULL);
	land = (char**) malloc((sizeof(char**)));
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		land[i] = line;
		i++;
		if (line == NULL)
			break;
	}
	map->land = land;
	return (map);
}
