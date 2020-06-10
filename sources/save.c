/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 18:12:51 by hwinston          #+#    #+#             */
/*   Updated: 2020/02/26 13:04:53 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	fheader(t_bmp *bmp, int w, int h)
{
	int		size;
	int		i;

	i = -1;
	while (++i < 14)
		bmp->fhead[i] = 0;
	size = 54 + (3 * w * h);
	bmp->fhead[0] = 'B';
	bmp->fhead[1] = 'M';
	bmp->fhead[2] = (unsigned char)(size);
	bmp->fhead[3] = (unsigned char)(size >> 8);
	bmp->fhead[4] = (unsigned char)(size >> 16);
	bmp->fhead[5] = (unsigned char)(size >> 24);
	bmp->fhead[10] = 54;
}

void	iheader(t_bmp *bmp, int w, int h)
{
	int i;

	i = -1;
	while (++i < 40)
		bmp->ihead[i] = 0;
	bmp->ihead[0] = 40;
	bmp->ihead[4] = (unsigned char)(w);
	bmp->ihead[5] = (unsigned char)(w >> 8);
	bmp->ihead[6] = (unsigned char)(w >> 16);
	bmp->ihead[7] = (unsigned char)(w >> 24);
	bmp->ihead[8] = (unsigned char)(h);
	bmp->ihead[9] = (unsigned char)(h >> 8);
	bmp->ihead[10] = (unsigned char)(h >> 16);
	bmp->ihead[11] = (unsigned char)(h >> 24);
	bmp->ihead[12] = 1;
	bmp->ihead[14] = 24;
}

void	write_rgb(t_bmp *bmp, t_var *v, int fd)
{
	int			i;
	int			j;
	int			x;
	int			y;
	const int	*pixels = (int *)v->img.dt;

	i = -1;
	while (++i < 3)
		bmp->pad[i] = 0;
	j = -1;
	while (++j < v->resy)
	{
		i = -1;
		while (++i < v->resx)
		{
			x = i;
			y = v->resy - 1 - j;
			bmp->clr = pixels[x + y * v->resx];
			write(fd, &bmp->clr, 3);
		}
		i = -1;
		while (++i < (4 - (v->resx * 3) % 4) % 4)
			write(fd, bmp->pad, 1);
	}
}

void	get_bmp(t_var *v)
{
	t_bmp	bmp;

	fheader(&bmp, v->resx, v->resy);
	iheader(&bmp, v->resx, v->resy);
	bmp.fd = open("save.bmp", O_WRONLY | O_CREAT, S_IRWXU);
	write(bmp.fd, bmp.fhead, 14);
	write(bmp.fd, bmp.ihead, 40);
	write_rgb(&bmp, v, bmp.fd);
	close(bmp.fd);
	quit(v);
}
