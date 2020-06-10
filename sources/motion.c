/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 16:06:16 by hwinston          #+#    #+#             */
/*   Updated: 2020/04/30 09:33:39 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Sprites motion.
*/

void	move_sp(t_var *v, int i)
{
	const double memx = v->sp.s[i].x;
	const double memy = v->sp.s[i].y;
	const double mx = (-v->rdirx + v->plnx) * M_SPEED / 3;
	const double my = (-v->rdiry + v->plny) * M_SPEED / 3;

	if (fabs(v->sp.s[i].x - v->posx) < 1.1 &&
	fabs(v->sp.s[i].y - v->posy) < 1.1)
	{
		v->life += v->resx / 300.0;
		if (v->life >= v->resx / 1.1 - v->resx / 13)
			game_over(v);
		return ;
	}
	if (v->map[(int)(v->sp.s[i].x + mx - 0.4)][(int)(v->sp.s[i].y)] != '1'
	&& v->map[(int)(v->sp.s[i].x + mx + 0.4)][(int)(v->sp.s[i].y)] != '1')
		v->sp.s[i].x += mx;
	if (v->map[(int)(v->sp.s[i].x)][(int)(v->sp.s[i].y + my - 0.4)] != '1'
	&& v->map[(int)(v->sp.s[i].x)][(int)(v->sp.s[i].y + my + 0.4)] != '1')
		v->sp.s[i].y += my;
	if (memx != v->sp.s[i].x || memy != v->sp.s[i].y)
	{
		v->map[(int)(memx)][(int)(memy)] = '0';
		v->map[(int)(v->sp.s[i].x)][(int)(v->sp.s[i].y)] = '2';
	}
}

/*
** Player motion, forward and backward.
*/

void	move_fb(t_var *v, int side)
{
	if (side == 1)
	{
		if (v->map[(int)(v->posx + v->dirx * v->m.spd)][(int)v->posy] == '0')
			v->posx += v->dirx * v->m.spd;
		if (v->map[(int)v->posx][(int)(v->posy + v->diry * v->m.spd)] == '0')
			v->posy += v->diry * v->m.spd;
	}
	else if (side == -1)
	{
		if (v->map[(int)(v->posx - v->dirx * v->m.spd)][(int)v->posy] == '0')
			v->posx -= v->dirx * v->m.spd;
		if (v->map[(int)v->posx][(int)(v->posy - v->diry * v->m.spd)] == '0')
			v->posy -= v->diry * v->m.spd;
	}
}

/*
** Player motion, left and right.
*/

void	move_lr(t_var *v, int side)
{
	if (side == -1)
	{
		if (v->map[(int)(v->posx - v->plnx * v->m.spd)][(int)v->posy] == '0')
			v->posx -= v->plnx * v->m.spd;
		if (v->map[(int)v->posx][(int)(v->posy - v->plny * v->m.spd)] == '0')
			v->posy -= v->plny * v->m.spd;
	}
	else if (side == 1)
	{
		if (v->map[(int)(v->posx + v->plnx * v->m.spd)][(int)v->posy] == '0')
			v->posx += v->plnx * v->m.spd;
		if (v->map[(int)v->posx][(int)(v->posy + v->plny * v->m.spd)] == '0')
			v->posy += v->plny * v->m.spd;
	}
}

/*
** Camera rotation.
*/

void	turn_cam(t_var *v, int side)
{
	const double old_d_x = v->dirx;
	const double old_plnx = v->plnx;

	if (side == -1)
	{
		v->dirx = v->dirx * cos(R_SPEED) - v->diry * sin(R_SPEED);
		v->diry = old_d_x * sin(R_SPEED) + v->diry * cos(R_SPEED);
		v->plnx = v->plnx * cos(R_SPEED) - v->plny * sin(R_SPEED);
		v->plny = old_plnx * sin(R_SPEED) + v->plny * cos(R_SPEED);
	}
	else if (side == 1)
	{
		v->dirx = v->dirx * cos(-R_SPEED) - v->diry * sin(-R_SPEED);
		v->diry = old_d_x * sin(-R_SPEED) + v->diry * cos(-R_SPEED);
		v->plnx = v->plnx * cos(-R_SPEED) - v->plny * sin(-R_SPEED);
		v->plny = old_plnx * sin(-R_SPEED) + v->plny * cos(-R_SPEED);
	}
}

/*
** Player motion hub.
*/

int		move(t_var *v)
{
	if (v->m.m_up == 1)
		move_fb(v, 1);
	if (v->m.m_down == 1)
		move_fb(v, -1);
	if (v->m.m_left == 1)
		move_lr(v, -1);
	if (v->m.m_right == 1)
		move_lr(v, 1);
	if (v->m.t_left == 1)
		turn_cam(v, -1);
	if (v->m.t_right == 1)
		turn_cam(v, 1);
	raycast(v);
	return (0);
}
