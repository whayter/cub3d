/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 22:09:15 by hwinston          #+#    #+#             */
/*   Updated: 2020/04/30 09:41:49 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Calculate distances between the player and sprites.
*/

static double	get_distances(t_var *v, int i)
{
	double	dist;

	dist = fabs((v->posx - v->sp.s[i].x) * v->posx - v->sp.s[i].x)
		+ (v->posy - v->sp.s[i].y) * (v->posy - v->sp.s[i].y);
	if (dist < 200)
		move_sp(v, i);
	return (dist);
}

/*
** Sort sprites by distances from the player.
*/

void			sort_sprites(t_var *v)
{
	int		i;
	double	dist[v->sp.n_sp];
	t_spos	sp;
	int		d_tmp;

	i = -1;
	while (++i < v->sp.n_sp)
		dist[i] = get_distances(v, i);
	i = -1;
	while (++i < v->sp.n_sp - 1)
	{
		if (dist[i] < dist[i + 1])
		{
			sp = v->sp.s[i];
			v->sp.s[i] = v->sp.s[i + 1];
			v->sp.s[i + 1] = sp;
			d_tmp = dist[i];
			dist[i] = dist[i + 1];
			dist[i + 1] = d_tmp;
			i = -1;
		}
	}
}

/*
** Calculate values needed for sprite drawing.
*/

void			get_val(t_var *v, int i)
{
	v->sp.spx = v->sp.s[i].x - v->posx;
	v->sp.spy = v->sp.s[i].y - v->posy;
	v->sp.inv = 1.0 / (v->plnx * v->diry - v->dirx * v->plny);
	v->sp.trx = v->sp.inv * (v->diry * v->sp.spx - v->dirx * v->sp.spy);
	v->sp.try = v->sp.inv * (-v->plny * v->sp.spx + v->plnx * v->sp.spy);
	v->sp.scrx = (int)((v->resx / 2) * (1 + v->sp.trx / v->sp.try));
	v->sp.h = ft_absval((int)(v->resy / v->sp.try));
	v->sp.strty = -v->sp.h / 2 + v->resy / 2;
	if (v->sp.strty < 0)
		v->sp.strty = 0;
	v->sp.endy = v->sp.h / 2 + v->resy / 2;
	if (v->sp.endy >= v->resy)
		v->sp.endy = v->resy - 1;
	v->sp.w = ft_absval((int)(v->resy / v->sp.try));
	v->sp.strtx = -v->sp.w / 2 + v->sp.scrx;
	if (v->sp.strtx < 0)
		v->sp.strtx = 0;
	v->sp.endx = v->sp.w / 2 + v->sp.scrx;
	if (v->sp.endx >= v->resx)
		v->sp.endx = v->resx - 1;
}

/*
** Draw sprites.
*/

void			draw_sprites(t_var *v, int x)
{
	int		d;
	int		y;
	int		sp_pxl;
	char	*pxl;

	v->sp.tx = (int)(256 * (x - (-v->sp.w / 2 + v->sp.scrx)) * \
				v->tx.w / v->sp.w) / 256;
	if (v->sp.try > 0 && x > 0 && x < v->resx && v->sp.try < v->sp.zbuf[x])
	{
		y = v->sp.strty - 1;
		while (++y < v->sp.endy)
		{
			d = y * 256 - v->resy * 128 + v->sp.h * 128;
			v->sp.ty = ((d * v->tx.h) / v->sp.h) / 256;
			pxl = v->img.dt + 4 * v->resx * y + x * 4;
			sp_pxl = 4 * v->sp.tx + 256 * v->sp.ty;
			if ((v->tx.dt[4][sp_pxl] & 0xFFFFFF) != 0)
				ft_memcpy(pxl, v->tx.dt[4] + sp_pxl, sizeof(int));
		}
	}
}

/*
** Get sprites functions hub.
*/

void			get_sprites(t_var *v)
{
	int i;
	int x;

	sort_sprites(v);
	i = -1;
	while (++i < v->sp.n_sp)
	{
		get_val(v, i);
		x = v->sp.strtx - 1;
		while (++x < v->sp.endx)
			draw_sprites(v, x);
	}
}
