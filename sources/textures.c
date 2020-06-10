/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:46:54 by hwinston          #+#    #+#             */
/*   Updated: 2020/04/30 11:34:19 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Get the floor and ceiling
** textures datas from xpm files.
*/

int		get_fl_text_data(t_var *v, int fl)
{
	if (fl == 0)
	{
		if (!(v->tx.fl_pt = mlx_xpm_file_to_image(v->mlx,
		v->tx.fl_path, &v->tx.w, &v->tx.h)))
			return (0);
		if (!(v->tx.fl_dt = mlx_get_data_addr(v->tx.fl_pt, &v->tx.bpp,
		&v->tx.size, &v->tx.endn)))
			return (0);
	}
	else
	{
		if (!(v->tx.ce_pt = mlx_xpm_file_to_image(v->mlx,
		v->tx.ce_path, &v->tx.w, &v->tx.h)))
			return (0);
		if (!(v->tx.ce_dt = mlx_get_data_addr(v->tx.ce_pt, &v->tx.bpp,
		&v->tx.size, &v->tx.endn)))
			return (0);
	}
	return (1);
}

/*
** Get textutes datas from xpm files.
*/

int		get_text_data(t_var *v)
{
	int i;

	i = -1;
	while (++i < 5)
		if (!(v->tx.pt[i] = mlx_xpm_file_to_image(v->mlx, v->tx.paths[i],
		&v->tx.w, &v->tx.h)) || !(v->tx.dt[i] = mlx_get_data_addr(v->tx.pt[i],
		&v->tx.bpp, &v->tx.size, &v->tx.endn)))
			return (TEXT_ERROR);
	if ((v->tx.fl_path != NULL && !(get_fl_text_data(v, 0))) ||
	(v->tx.ce_path != NULL && !(get_fl_text_data(v, 1))))
		return (TEXT_ERROR);
	if (!(v->tx.pt[5] = mlx_xpm_file_to_image(v->mlx,
	"./assets/general/trgt.xpm", &v->s_trgt, &v->s_trgt)))
		return (TEXT_ERROR);
	v->img.trgt = mlx_get_data_addr(v->tx.pt[5], &v->tx.bpp,
	&v->tx.size, &v->tx.endn);
	if (!(v->tx.pt[6] = mlx_xpm_file_to_image(v->mlx,
	"./assets/general/gun.xpm", &v->s_gun, &v->s_gun)))
		return (TEXT_ERROR);
	v->img.gun = mlx_get_data_addr(v->tx.pt[6],
	&v->tx.bpp, &v->tx.size, &v->tx.endn);
	return (0);
}

/*
** Store texture paths from the .cub file.
*/

int		get_text_path(t_var *v, char *s, int i)
{
	if ((v->r = check_path_line(s)) < 0)
		return (v->r);
	if (i == 5)
	{
		if (v->tx.fl_path != NULL)
			return (MUL_ERROR);
		if (!(v->tx.fl_path = ft_strdup(ft_strchr(s, '.'))))
			return (MEM_ERROR);
	}
	else if (i == 6)
	{
		if (v->tx.ce_path != NULL)
			return (MUL_ERROR);
		if (!(v->tx.ce_path = ft_strdup(ft_strchr(s, '.'))))
			return (MEM_ERROR);
	}
	else
	{
		if (v->tx.paths[i] != NULL)
			return (MUL_ERROR);
		if (!(v->tx.paths[i] = ft_strdup(ft_strchr(s, '.'))))
			return (MEM_ERROR);
	}
	return (0);
}

/*
** Check if we are looking for the ceiling
** texture file path or the floor texture file path.
*/

int		get_fl_text(t_var *v, char *line)
{
	int r;

	r = 0;
	if (ft_strncmp(line, "F ", 2) == 0)
		r = get_text_path(v, line, 5);
	else if (ft_strncmp(line, "C ", 2) == 0)
		r = get_text_path(v, line, 6);
	return (r);
}
