/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:20:32 by hwinston          #+#    #+#             */
/*   Updated: 2020/04/30 09:38:34 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		main(int ac, char **av)
{
	t_var	v;
	int		r;

	if ((r = check_params(&v, ac, av)) <= 0)
		return (error(r));
	if ((r = check_file(&v, av[1])) < 0)
		return (error(r));
	if ((v.mlx = mlx_init()) == NULL)
		return (error(MEM_ERROR));
	if ((r = last_inits(&v)) < 0)
	{
		error(r);
		return (quit(&v));
	}
	v.open = 1;
	if ((v.win = mlx_new_window(v.mlx, v.resx, v.resy, NAME)) == NULL)
		return (quit(&v));
	mlx_do_key_autorepeatoff(v.mlx);
	mlx_hook(v.win, 2, 1, key_press, &v);
	mlx_hook(v.win, 3, 2, key_rel, &v);
	mlx_hook(v.win, 33, 0, quit, &v);
	mlx_loop_hook(v.mlx, move, &v);
	mlx_loop(v.mlx);
}
