/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:08:33 by mfornovi          #+#    #+#             */
/*   Updated: 2025/12/16 13:08:37 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	only_spaces_in_line(char *buff, int *i)
{
	int	n;

	n = *i;
	while (buff[n] != '\n')
	{
		if (buff[n] != '	' && buff[n] != ' ')
			return (false);
		n++;
	}
	return (true);
}

char	*save_line(char *buff, int *i)
{
	char	*line;
	int		size;
	int		n;
	int		j;

	n = *i;
	j = 0;
	while (buff[n] && buff[n] != '\n')
		n++;
	size = n - *i;
	line = ft_calloc(sizeof(char), size + 1);
	while (j < size)
	{
		line[j] = buff[*i];
		*i = *i + 1;
		j++;
	}
	line[j] = 0;
	*i = *i + 1;
	return (line);
}

int	count_nls(char *buff, int n)
{
	int	nls;

	nls = 1;
	while (buff[n])
	{
		if (buff[n] == '\n')
			nls++;
		n++;
	}
	return (nls);
}

char	**split_by_nl(char *buff, int *i, t_compass *comp)
{
	char	**split;
	int		size;
	int		n;
	int		longest;

	n = 0;
	longest = 0;
	size = count_nls(buff, *i);
	split = (char **)ft_calloc(sizeof(char *), size + 1);
	while (n < size)
	{
		split[n] = save_line(buff, i);
		if (longest < (int)ft_strlen(split[n]))
			longest = ft_strlen(split[n]);
		n++;
	}
	split[n] = NULL;
	comp->map_width = longest;
	comp->map_height = size;
	return (split);
}
