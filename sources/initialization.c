/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 12:24:19 by hwinston          #+#    #+#             */
/*   Updated: 2020/04/30 09:30:43 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Varialbles initialisation.
*/

void	v_init(t_var *v)
{
	v->rx_max = 0;
	v->ry_max = 0;
	v->posx = -1;
	v->posy = -1;
	v->resx = 0;
	v->resy = 0;
	v->map_h = 0;
	v->map_w = 0;
	v->m.spd = M_SPEED;
	v->tx.fl_path = NULL;
	v->tx.ce_path = NULL;
	v->fl.f_clr = -1;
	v->fl.c_clr = -1;
	v->sp.n_sp = 0;
	v->cnt = 0;
	v->sht = 0;
	v->open = 0;
}

/*
** Player direction initialisation
*/

void	init_dir(t_var *v, char c)
{
	if (c == 'N')
	{
		v->dirx = -1;
		v->diry = 0;
	}
	else if (c == 'S')
	{
		v->dirx = 1;
		v->diry = 0;
	}
	else if (c == 'E')
	{
		v->dirx = 0;
		v->diry = 1;
	}
	else if (c == 'W')
	{
		v->dirx = 0;
		v->diry = -1;
	}
}

/*
** Player plane initialisation
*/

void	init_plane(t_var *v, char c)
{
	if (c == 'N' || c == 'S')
	{
		v->plnx = -v->diry * 0.66;
		v->plny = -v->dirx * 0.66;
	}
	else if (c == 'E' || c == 'W')
	{
		v->plnx = v->diry * 0.66;
		v->plny = v->dirx * 0.66;
	}
}

void	set_data(t_var *v, int x)
{
	v->camx = 2 * x / (double)v->resx - 1;
	v->rdirx = v->dirx + v->plnx * v->camx;
	v->rdiry = v->diry + v->plny * v->camx;
	v->mapx = (int)v->posx;
	v->mapy = (int)v->posy;
	v->d_dstx = ft_absval(1 / v->rdirx);
	v->d_dsty = ft_absval(1 / v->rdiry);
}

/*
** Player initialisation hub
*/

void	init_player(t_var *v, int x, int y, char c)
{
	v->posx = (double)x + 0.5;
	v->posy = (double)y + 0.5;
	init_dir(v, c);
	init_plane(v, c);
	init_motion(v);
	v->life = 0;
}
