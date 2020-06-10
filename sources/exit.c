/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:20:32 by hwinston          #+#    #+#             */
/*   Updated: 2020/04/30 09:38:34 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_everything(t_var *v)
{
	int i;

	i = -1;
	while (++i < 7)
	{
		if (v->tx.pt[i] != NULL)
			mlx_destroy_image(v->mlx, v->tx.pt[i]);
	}
	free(v->tx.pt);
	if (v->tx.ce_path != NULL)
		mlx_destroy_image(v->mlx, v->tx.ce_pt);
	if (v->tx.fl_path != NULL)
		mlx_destroy_image(v->mlx, v->tx.fl_pt);
	ft_free_strs(v->map, -1, 0);
	ft_free_strs(v->tx.paths, 5, 0);
	ft_free_str(&v->tx.ce_path, 0);
	ft_free_str(&v->tx.fl_path, 0);
	free(v->tx.dt);
	free(v->sp.s);
	free(v->sp.zbuf);
}

int		quit(t_var *v)
{
	if (v->open == 1)
		free_everything(v);
	if (v->save != 1 && v->open == 1)
		mlx_destroy_window(v->mlx, v->win);
	exit(0);
	return (0);
}

void	game_over(t_var *v)
{
	system("aplay -q -c 3 --duration=2 ./assets/sounds/pain.wav &");
	system("sleep 4s");
	quit(v);
}

int		error(int err)
{
	if (err == 0)
		ft_putstr("Error\nThe map file is missing\n");
	else if (err == ARG_ERROR)
		ft_putstr("Error\nBad arguments\n");
	else if (err == FILENAME_ERROR)
		ft_putstr("Error\nThe map file is not in the right format\n");
	else if (err == READ_ERROR)
		ft_putstr("Error\nThe map file could not be read\n");
	else if (err == MEM_ERROR)
		ft_putstr("Error\nMemory allocation failed\n");
	else if (err == RES_ERROR)
		ft_putstr("Error\nBad resolution\n");
	else if (err == TEXT_ERROR)
		ft_putstr("Error\nBad texture path\n");
	else if (err == MAP_ERROR)
		ft_putstr("Error\nInvalid map\n");
	else if (err == COLOR_ERROR)
		ft_putstr("Error\nInvalid color\n");
	else if (err == TEXT_MISSING)
		ft_putstr("Error\nSome texture files are missing\n");
	else if (err == RES_MISSING)
		ft_putstr("Error\nResolution is missing\n");
	else if (err == MUL_ERROR)
		ft_putstr("Error\nToo many informations\n");
	return (0);
}

int		partial_free(t_var *v, int r)
{
	ft_free_strs(v->tx.paths, 5, 0);
	ft_free_str(&v->tx.ce_path, 0);
	ft_free_str(&v->tx.fl_path, 0);
	ft_free_strs(v->file, -1, 0);
	return (r);
}
