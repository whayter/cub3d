/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:06:59 by hwinston          #+#    #+#             */
/*   Updated: 2020/02/26 14:49:41 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	resize_image(t_var *v, t_tmp *t, void **pt, char **dt)
{
	t->size_x = 1.0 * t->s / t->new_s;
	t->size_y = 1.0 * t->s / t->new_s;
	*pt = mlx_new_image(v->mlx, t->new_s, t->new_s);
	*dt = mlx_get_data_addr(*pt, &t->bpp, &t->size, &t->endn);
	t->y = -1;
	while (++t->y < t->new_s)
	{
		t->x = -1;
		while (++t->x < t->new_s)
		{
			t->src = 4 * (int)(t->x * t->size_x)
			+ 4 * t->s * (int)(t->y * t->size_y);
			t->dst = t->x * 4 + t->y * 4 * t->new_s;
			ft_memcpy(*dt + t->dst, t->fsrc + t->src, sizeof(int));
		}
	}
}

void	draw_target(t_var *v)
{
	t_pl	p;
	t_tmp	t;

	t.s = 32;
	t.new_s = v->resx > v->resy ? v->resy / 20 : v->resx / 20;
	t.fsrc = v->img.trgt;
	resize_image(v, &t, &v->tx.trgt_pt, &v->tx.trgt_dt);
	p.strtx = v->resx / 2 - t.new_s / 2;
	p.strty = v->resy / 2 - t.new_s;
	p.endx = v->resx / 2 + t.new_s / 2;
	p.endy = v->resy / 2;
	p.x = p.strtx - 1;
	p.j = 0;
	while (++p.x < p.endx)
	{
		p.y = p.strty - 1;
		p.i = 0;
		while (++p.y < p.endy)
		{
			init_steps(v, &p, &t);
			if ((v->tx.trgt_dt[p.d] & 0xFFFFFF) != 0)
				ft_memcpy(p.pxl, v->tx.trgt_dt + p.d, sizeof(int));
		}
		p.j++;
	}
}

void	draw_gun(t_var *v)
{
	t_pl	p;
	t_tmp	t;

	t.s = 256;
	t.new_s = v->resx > v->resy ? v->resy * 0.4 : v->resx * 0.4;
	t.fsrc = v->img.gun;
	resize_image(v, &t, &v->tx.gun_pt, &v->tx.gun_dt);
	p.strtx = v->resx / 2;
	p.strty = v->resy - t.new_s;
	p.endx = v->resx / 2 + t.new_s;
	p.endy = v->resy;
	p.y = p.strty - 1;
	p.j = 0;
	while (++p.y < p.endy)
	{
		p.x = p.strtx - 1;
		p.i = 0;
		while (++p.x < p.endx)
		{
			init_steps(v, &p, &t);
			if ((v->tx.gun_dt[p.d] & 0xFFFFFF) != 0)
				ft_memcpy(p.pxl, v->tx.gun_dt + p.d, sizeof(int));
		}
		p.j++;
	}
}

void	draw_life(t_var *v)
{
	t_pl		p;
	const int	clr = RED;

	p.strtx = v->resx / 13;
	p.strty = v->resy / 16;
	p.endx = v->resx / 1.1 - v->life;
	p.endy = v->resy / 13;
	p.x = p.strtx - 1;
	while (++p.x < p.endx)
	{
		p.y = p.strty - 1;
		while (++p.y < p.endy)
		{
			p.pxl = v->img.dt + 4 * v->resx * p.y + p.x * 4;
			ft_memcpy(p.pxl, &clr, sizeof(int));
		}
	}
}

void	set_player(t_var *v)
{
	draw_life(v);
	draw_target(v);
	draw_gun(v);
}
