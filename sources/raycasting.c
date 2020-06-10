/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:43:26 by hwinston          #+#    #+#             */
/*   Updated: 2020/04/29 17:18:11 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_side_dist(t_var *v)
{
	if (v->rdirx < 0)
	{
		v->step_x = -1;
		v->s_dstx = (v->posx - v->mapx) * v->d_dstx;
	}
	else
	{
		v->step_x = 1;
		v->s_dstx = (v->mapx + 1.0 - v->posx) * v->d_dstx;
	}
	if (v->rdiry < 0)
	{
		v->step_y = -1;
		v->s_dsty = (v->posy - v->mapy) * v->d_dsty;
	}
	else
	{
		v->step_y = 1;
		v->s_dsty = (v->mapy + 1.0 - v->posy) * v->d_dsty;
	}
}

void	perform_dda(t_var *v)
{
	v->hit = 0;
	while (v->hit == 0)
	{
		if (v->s_dstx < v->s_dsty)
		{
			v->s_dstx += v->d_dstx;
			v->mapx += v->step_x;
			v->side = (v->rdirx > 0) ? 1 : 0;
		}
		else
		{
			v->s_dsty += v->d_dsty;
			v->mapy += v->step_y;
			v->side = (v->rdiry > 0) ? 3 : 2;
		}
		if (v->map[v->mapx][v->mapy] == '1')
			v->hit = 1;
	}
	if (v->side == 0 || v->side == 1)
		v->w_dst = (v->mapx - v->posx + (1 - v->step_x) / 2) / v->rdirx;
	else
		v->w_dst = (v->mapy - v->posy + (1 - v->step_y) / 2) / v->rdiry;
}

void	get_walls_data(t_var *v)
{
	v->line_h = (int)(v->resy / v->w_dst);
	v->d_strt = -v->line_h / 2 + v->resy / 2;
	if (v->d_strt < 0)
		v->d_strt = 0;
	v->d_end = v->line_h / 2 + v->resy / 2;
	if (v->d_end >= v->resy)
		v->d_end = v->resy - 1;
	if (v->side == 0 || v->side == 1)
		v->tx.w_x = v->posy + v->w_dst * v->rdiry;
	else
		v->tx.w_x = v->posx + v->w_dst * v->rdirx;
	v->tx.w_x -= floor(v->tx.w_x);
	v->tx.x = (int)(v->tx.w_x * (double)v->tx.w);
	v->tx.step = 1.0 * v->tx.h / v->line_h;
	v->tx.pos = (v->d_strt - v->resy / 2 + v->line_h / 2) * v->tx.step;
}

/*
** Draw textures in the image
*/

void	draw_textures(t_var *v, int x)
{
	char	*pxl;
	int		y;
	int		z;

	y = -1;
	while (++y < v->resy)
	{
		pxl = v->img.dt + 4 * v->resx * y + x * 4;
		if (v->fl.c_clr >= 0 && y < v->d_strt)
			ft_memcpy(pxl, &v->fl.c_clr, sizeof(int));
		if (y >= v->d_strt && y <= v->d_end)
		{
			v->tx.y = (int)v->tx.pos & (v->tx.h - 1);
			v->tx.pos += v->tx.step;
			z = 4 * v->tx.x + 256 * v->tx.y;
			ft_memcpy(pxl, v->tx.dt[v->side] + z, sizeof(int));
		}
		if (v->fl.f_clr >= 0 && y > v->d_end)
			ft_memcpy(pxl, &v->fl.f_clr, sizeof(int));
	}
	v->sp.zbuf[x] = v->w_dst;
}

/*
** Raycasting hub
*/

void	raycast(t_var *v)
{
	int x;

	v->img.ptr = mlx_new_image(v->mlx, v->resx, v->resy);
	v->img.dt = mlx_get_data_addr(v->img.ptr,
	&v->img.bpp, &v->img.size, &v->img.endn);
	if (v->tx.ce_path != NULL)
		get_floors(v, -1, v->resy / 2, 1);
	if (v->tx.fl_path != NULL)
		get_floors(v, v->resy / 2 - 1, v->resy, 0);
	x = -1;
	while (++x < v->resx)
	{
		set_data(v, x);
		get_side_dist(v);
		perform_dda(v);
		get_walls_data(v);
		draw_textures(v, x);
	}
	get_sprites(v);
	set_player(v);
	if (v->save == 1)
		get_bmp(v);
	mlx_put_image_to_window(v->mlx, v->win, v->img.ptr, 0, 0);
	destroy_img(v);
}
