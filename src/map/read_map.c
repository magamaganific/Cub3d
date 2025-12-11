/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 19:32:46 by frlorenz          #+#    #+#             */
/*   Updated: 2025/12/11 18:05:17 by frlorenz         ###   ########.fr       */
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

char **ft_get_map(void)
{
	char **map;
	
	map = malloc(sizeof(char *) * 8);
	map[0] = "11111111111";
	map[1] = "10001000001";
	map[2] = "10101011101";
	map[3] = "10101010001";
	map[4] = "10101010101";
	map[5] = "1N100010001";
	map[6] = "11111111111";
	map[7] = NULL;
	return(map);
}
