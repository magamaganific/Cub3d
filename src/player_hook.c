/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlorenz <frlorenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:05:51 by mfornovi          #+#    #+#             */
/*   Updated: 2026/02/24 13:01:39 by frlorenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	move_forward(t_compass *comp)
{
	double	angle;
	double	m_cos;
	double	m_sin;

	angle = comp->sight->angle;
	m_cos = cos(degree_to_radians(angle)) * SPEED;
	m_sin = sin(degree_to_radians(angle)) * SPEED;
	if (!corner_collide(comp, comp->player_x + m_cos, comp->player_y + m_sin))
	{
		comp->player_x += m_cos;
		comp->player_y += m_sin;
		draw_raycaster(comp);
	}
}

static void	move_backwards(t_compass *comp)
{
	double	angle;
	double	m_cos;
	double	m_sin;

	angle = comp->sight->angle;
	m_cos = cos(degree_to_radians(angle - 180)) * SPEED;
	m_sin = sin(degree_to_radians(angle - 180)) * SPEED;
	if (!corner_collide(comp, comp->player_x + m_cos, comp->player_y + m_sin))
	{
		comp->player_x += m_cos;
		comp->player_y += m_sin;
		draw_raycaster(comp);
	}
}

static void	move_right(t_compass *comp)
{
	double	angle;
	double	m_cos;
	double	m_sin;

	angle = comp->sight->angle;
	m_cos = cos(degree_to_radians(angle + 90)) * SPEED;
	m_sin = sin(degree_to_radians(angle + 90)) * SPEED;
	if (!corner_collide(comp, comp->player_x + m_cos, comp->player_y + m_sin))
	{
		comp->player_x += m_cos;
		comp->player_y += m_sin;
		draw_raycaster(comp);
	}
}

static void	move_left(t_compass *comp)
{
	double	angle;
	double	m_cos;
	double	m_sin;

	angle = comp->sight->angle;
	m_cos = cos(degree_to_radians(angle - 90)) * SPEED;
	m_sin = sin(degree_to_radians(angle - 90)) * SPEED;
	if (!corner_collide(comp, comp->player_x + m_cos, comp->player_y + m_sin))
	{
		comp->player_x += m_cos;
		comp->player_y += m_sin;
		draw_raycaster(comp);
	}
}

void	player_hook(void *param)
{
	t_compass	*comp;

	comp = (t_compass *)param;
	if (mlx_is_key_down(comp->mlx, MLX_KEY_W))
		move_forward(comp);
	if (mlx_is_key_down(comp->mlx, MLX_KEY_S))
		move_backwards(comp);
	if (mlx_is_key_down(comp->mlx, MLX_KEY_D))
		move_right(comp);
	if (mlx_is_key_down(comp->mlx, MLX_KEY_A))
		move_left(comp);
	if (mlx_is_key_down(comp->mlx, MLX_KEY_LEFT))
	{
		comp->sight->angle -= R_ITER;
		draw_raycaster(comp);
	}
	if (mlx_is_key_down(comp->mlx, MLX_KEY_RIGHT))
	{
		comp->sight->angle += R_ITER;
		draw_raycaster(comp);
	}
}
