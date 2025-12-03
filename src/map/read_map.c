/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 19:32:46 by frlorenz          #+#    #+#             */
/*   Updated: 2025/12/03 09:55:11 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



t_map *ft_read_map(char *path)
{
	int		fd;
	char	*line;
	t_map	*map;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
	}
	map = (t_map*) malloc(sizeof(t_map*));
	if (!map)
		return (NULL);
	return (map);
}
