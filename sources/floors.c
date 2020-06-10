/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 22:11:59 by hwinston          #+#    #+#             */
/*   Updated: 2020/02/26 14:36:19 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_floors_data(t_var *v, int start, int tx)
{
	v->fl.rdirx = (tx == 0) ? v->dirx - v->plnx : -v->dirx + v->plnx;
	v->fl.rdiry = (tx == 0) ? v->diry - v->plny : -v->diry + v->plny;
	v->fl.rdirxx = (tx == 0) ? v->dirx + v->plnx : -v->dirx - v->plnx;
	v->fl.rdiryy = (tx == 0) ? v->diry + v->plny : -v->diry - v->plny;
	v->fl.p = start - v->resy / 2;
	v->fl.poz = 0.5 * v->resy;
	v->fl.row_d = v->fl.poz / v->fl.p;
	v->fl.step_x = v->fl.row_d * (v->fl.rdirxx - v->fl.rdirx) / v->resx;
	v->fl.step_y = v->fl.row_d * (v->fl.rdiryy - v->fl.rdiry) / v->resx;
	v->fl.fx = v->posx + v->fl.row_d * v->fl.rdirx;
	v->fl.fy = v->posy + v->fl.row_d * v->fl.rdiry;
}

void	get_floors(t_var *v, int start, int end, int tx)
{
	int		x;
	char	*dest;
	void	*pxl;

	while (++start < end)
	{
		get_floors_data(v, start, tx);
		x = -1;
		while (++x < v->resx)
		{
			v->fl.cx = (int)v->fl.fx;
			v->fl.cy = (int)v->fl.fy;
			v->fl.x = (int)(v->tx.w * (v->fl.fx - v->fl.cx)) & (v->tx.w - 1);
			v->fl.y = (int)(v->tx.h * (v->fl.fy - v->fl.cy)) & (v->tx.h - 1);
			v->fl.fx += v->fl.step_x;
			v->fl.fy += v->fl.step_y;
			dest = v->img.dt + 4 * v->resx * start + x * 4;
			if (tx == 0)
				pxl = v->tx.fl_dt + 4 * v->fl.x + 256 * v->fl.y;
			else
				pxl = v->tx.ce_dt + 4 * v->fl.x + 256 * v->fl.y;
			ft_memcpy(dest, pxl, sizeof(int));
		}
	}
}
