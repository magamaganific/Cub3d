/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:44:13 by mfornovi          #+#    #+#             */
/*   Updated: 2025/12/18 12:44:15 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	print_accepted_input(void)
{
	printf("Accepted input: \n	./Game [MAP PATH]\n");
	printf("		(maps available in the \"maps\" directory)\n");
}

void	wrong_format(void)
{
	printf("Make sure your .cub has valid contents\n");
}

void	error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

bool	check_map(char *buff, int n)
{
	int	player;

	player = 0;
	while (buff[n])
	{
		if (!(buff[n] != '1' || buff[n] != '0' || buff[n] != '\n'
				|| buff[n] != 'N' || buff[n] != 'S' || buff[n] != 'W'
				|| buff[n] != 'E' || buff[n] != ' '))
			return (false);
		if (buff[n] == 'N' || buff[n] == 'S' || buff[n] == 'W'
			|| buff[n] == 'E')
		{
			if (player == 1)
				return (printf("More than one player\n"), false);
			player = 1;
		}
		n++;
	}
	if (!player)
		return (printf("Player mising\n"), false);
	return (true);
}
