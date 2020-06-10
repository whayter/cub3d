/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 16:05:07 by hwinston          #+#    #+#             */
/*   Updated: 2020/04/30 09:37:38 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Motion variables initialisation.
*/

void	init_motion(t_var *v)
{
	v->m.m_up = 0;
	v->m.m_down = 0;
	v->m.m_left = 0;
	v->m.m_right = 0;
	v->m.t_left = 0;
	v->m.t_right = 0;
}

/*
** Check for key press events.
*/

int		key_press(int key, t_var *v)
{
	if (key == QUIT)
		quit(v);
	if (key == UP)
		v->m.m_up = 1;
	if (key == DOWN)
		v->m.m_down = 1;
	if (key == LEFT)
		v->m.m_left = 1;
	if (key == RIGHT)
		v->m.m_right = 1;
	if (key == LCAM)
		v->m.t_left = 1;
	if (key == RCAM)
		v->m.t_right = 1;
	if (key == SPACE)
		v->m.spd = M_RSPEED;
	if (key == SHOOT)
		gunshot(v, ++v->sht);
	return (0);
}

/*
** Check for key release events.
*/

int		key_rel(int key, t_var *v)
{
	if (key == UP)
		v->m.m_up = 0;
	if (key == DOWN)
		v->m.m_down = 0;
	if (key == LEFT)
		v->m.m_left = 0;
	if (key == RIGHT)
		v->m.m_right = 0;
	if (key == LCAM)
		v->m.t_left = 0;
	if (key == RCAM)
		v->m.t_right = 0;
	if (key == SPACE)
		v->m.spd = M_SPEED;
	if (key == SHOOT)
		v->sht = 0;
	return (0);
}
