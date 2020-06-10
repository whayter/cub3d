/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 16:25:17 by hwinston          #+#    #+#             */
/*   Updated: 2020/04/30 09:26:50 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Get the total height of the map.
*/

static int		get_dimensions(t_var *v, int i)
{
	int size;
	int f_size;

	f_size = i;
	while (v->file[f_size])
		f_size++;
	while (v->file[i] != 0 && v->file[i][0] != '\0')
	{
		size = 0;
		if (v->file[i][0] == '\0' && v->file[i + 1])
			return (-1);
		while (v->file[i][size])
			size++;
		v->map_w = v->map_w < size ? size : v->map_w;
		i++;
		v->map_h++;
	}
	if (f_size - i > 0)
		return (-1);
	return (v->map_h);
}

/*
** Check if the given char is valid.
*/

int				is_valid(char c)
{
	if (c == '0' || c == '2')
		return (1);
	else if (c == '1')
		return (2);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (3);
	else if (c == ' ')
		return (4);
	else if (c == 'x')
		return (-1);
	return (0);
}

/*
** Store the map in p->m with the maximum width.
*/

static int		get_p_m(t_var *v, t_m_parse *p)
{
	int i;
	int j;
	int k;

	i = v->m_strt - 1;
	k = -1;
	while (v->file[++i])
	{
		if (!(p->m[++k] = malloc(sizeof(char) * (v->map_w + 1))))
			return (MEM_ERROR);
		j = -1;
		while (v->file[i][++j])
		{
			if (v->file[i][j] == '2')
				v->sp.n_sp++;
			p->m[k][j] = v->file[i][j];
		}
		while (j < v->map_w)
			p->m[k][j++] = ' ';
		p->m[k][j] = '\0';
	}
	p->m[++k] = 0;
	return (1);
}

/*
** Map parsing hub.
*/

int				check_map(t_var *v)
{
	t_m_parse	p;

	if (get_dimensions(v, v->m_strt) < 3)
		return (MAP_ERROR);
	if (!(p.m = malloc(sizeof(char *) * (v->map_h + 1))))
		return (MEM_ERROR);
	if (get_p_m(v, &p) < 0)
		return (ft_free_strs(p.m, -1, MEM_ERROR));
	p.wntd = 1;
	p.r = 'x';
	if (locate_player(v, &p) != 1)
		return (ft_free_strs(p.m, -1, MAP_ERROR));
	if (!(locate_accessible_area(v, &p)))
		return (ft_free_strs(p.m, -1, MAP_ERROR));
	if (!(check_contours(v, &p)))
		return (ft_free_strs(p.m, -1, MAP_ERROR));
	return (ft_free_strs(p.m, -1, 1));
}
