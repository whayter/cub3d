/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 16:38:14 by hwinston          #+#    #+#             */
/*   Updated: 2020/04/20 16:02:49 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	delete_sprite(t_var *v, double x, double y)
{
	int i;
	int hit;

	hit = 0;
	i = -1;
	while (hit == 0 && ++i < v->sp.n_sp)
	{
		if ((x - v->sp.s[i].x > -0.3 && x - v->sp.s[i].x < 0.3) &&
		(y - v->sp.s[i].y > -0.3 && y - v->sp.s[i].y < 0.3))
		{
			v->map[(int)x][(int)y] = '0';
			v->sp.s[i].x = -1000;
			v->sp.s[i].y = -1000;
			hit = 1;
		}
	}
}

void	gunshot(t_var *v, int sht)
{
	int		hit;
	double	tirx;
	double	tiry;

	if (sht > 1)
		return ;
	system("aplay -q -c 2 ./assets/sounds/shot.wav &");
	tirx = v->posx;
	tiry = v->posy;
	hit = 0;
	while (hit == 0)
	{
		if (v->map[(int)tirx][(int)tiry] == '2')
		{
			delete_sprite(v, tirx, tiry);
			hit = 1;
		}
		else if (v->map[(int)tirx][(int)tiry] == '1')
			hit = 1;
		tirx += v->dirx;
		tiry += v->diry;
	}
}
