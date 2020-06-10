/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 12:24:19 by hwinston          #+#    #+#             */
/*   Updated: 2020/04/30 09:30:43 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Check parameters.
*/

int		check_params(t_var *v, int ac, char **av)
{
	v->save = 0;
	if (ac < 2)
		return (0);
	if ((av[2] && ft_strcmp(av[2], "--save") != 0) || ac >= 4)
		return (ARG_ERROR);
	else if ((av[2] && ft_strcmp(av[2], "--save") == 0))
		v->save = 1;
	return (1);
}

/*
** Get the resolution of the screen.
*/

int		get_screen_size(t_var *v)
{
	if (!(mlx_get_screen_size(v->mlx, &v->rx_max, &v->ry_max)))
		return (RES_ERROR);
	if (v->resx > v->rx_max)
		v->resx = v->rx_max;
	if (v->resy > v->ry_max)
		v->resy = v->ry_max;
	return (0);
}

/*
** Last initialisations before opening the window.
*/

int		last_inits(t_var *v)
{
	int r;

	if ((r = get_screen_size(v)) < 0)
		return (r);
	if (!(v->sp.zbuf = malloc(sizeof(double) * v->resx)))
		return (MEM_ERROR);
	if (!(v->tx.dt = malloc(sizeof(char *) * 5)))
		return (MEM_ERROR);
	if (!(v->tx.pt = malloc(sizeof(void *) * 7)))
		return (MEM_ERROR);
	if ((r = get_text_data(v)) < 0)
		return (r);
	if (v->save == 1)
		raycast(v);
	return (0);
}

/*
** Destroy images for freeing pointers and data.
*/

void	destroy_img(t_var *v)
{
	mlx_destroy_image(v->mlx, v->tx.trgt_pt);
	mlx_destroy_image(v->mlx, v->tx.gun_pt);
	mlx_destroy_image(v->mlx, v->img.ptr);
}

/*
** Steps initialisation for writing in an image.
*/

void	init_steps(t_var *v, t_pl *p, t_tmp *t)
{
	p->d = 4 * t->new_s * p->j + p->i * 4;
	p->pxl = v->img.dt + 4 * v->resx * p->y + p->x * 4;
	p->i++;
}
