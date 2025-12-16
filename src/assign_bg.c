/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_bg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:07:59 by mfornovi          #+#    #+#             */
/*   Updated: 2025/12/16 13:08:09 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	save_color(char *buff, int *i)
{
	int		color;
	int		start;
	int		n;
	char	*num;

	start = *i;
	n = -1;
	while (buff[*i] >= '0' && buff[*i] <= '9')
		*i = *i + 1;
	if (*i - start > 4 || *i == start)
		return (-1);
	num = ft_calloc(sizeof(char),*i - start + 1);
	if (!num)
		return (-1);
	while (start <= *i)
		num[++n] = buff[start++];
	num[n] = 0;
	color = ft_atoi(num);
	*i = *i + 1;
	free(num);
	return (color & 0xff);
}

bool	fill_f(char *buff, int *i, t_compass *comp)
{
	int		red;
	int		blue;
	int		green;

	comp->f = 0;
	*i = *i + 1;
	while (buff[*i] == '	' || buff[*i] == ' ')
		*i = *i + 1;
	red = save_color(buff, i);
	if (red == -1)
		return (false);
	blue = save_color(buff, i);
	if (blue == -1)
		return (false);
	green = save_color(buff, i);
	if (green == -1)
		return (false);
	comp->f = (red << 24) | (green << 16) | (blue << 8) | 255;
	return (true);
}

bool	fill_c(char *buff, int *i, t_compass *comp)
{
	int		red;
	int		blue;
	int		green;

	comp->c = 0;
	*i = *i + 1;
	while (buff[*i] == '	' || buff[*i] == ' ')
		*i = *i + 1;
	red = save_color(buff, i);
	if (red == -1)
		return (false);
	green = save_color(buff, i);
	if (green == -1)
		return (false);
	blue = save_color(buff, i);
	if (blue == -1)
		return (false);
	comp->c = (red << 24) | (green << 16) | (blue << 8) | 255;
	return (true);
}

void	set_bg(void *param)
{
	const t_compass		*comp;
	int					x;
	int					y;

	comp = (t_compass *)param;
	mlx_resize_image(comp->bg, comp->mlx->width, comp->mlx->height);
	x = 0;
	while (x < comp->mlx->width)
	{
		y = 0;
		while (y < (comp->mlx->height / 2))
		{
			mlx_put_pixel(comp->bg, x, y, comp->f);
			y++;
		}
		while (y < comp->mlx->height)
		{
			mlx_put_pixel(comp->bg, x, y, comp->c);
			y++;
		}
		x++;
	}
}
