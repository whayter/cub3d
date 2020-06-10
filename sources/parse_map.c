/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 16:29:19 by hwinston          #+#    #+#             */
/*   Updated: 2020/04/30 09:27:43 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Replace char at the given position.
*/

static int		replace(t_m_parse *p, int x, int y)
{
	p->m[x][y] = p->r;
	return (1);
}

/*
** Look for a specified char around the given position.
*/

static int		look_around(t_var *v, t_m_parse *p, int op)
{
	int n;

	n = 0;
	if (p->x - 1 >= 0 && is_valid(p->m[p->x - 1][p->y]) == p->wntd)
		n += op == 1 ? replace(p, p->x - 1, p->y) : 1;
	if (p->x + 1 <= v->map_h - 1 && is_valid(p->m[p->x + 1][p->y]) == p->wntd)
		n += op == 1 ? replace(p, p->x + 1, p->y) : 1;
	if (p->y - 1 >= 0 && is_valid(p->m[p->x][p->y - 1]) == p->wntd)
		n += op == 1 ? replace(p, p->x, p->y - 1) : 1;
	if (p->m[p->x][p->y + 1] != '\0' &&
	is_valid(p->m[p->x][p->y + 1]) == p->wntd)
		n += op == 1 ? replace(p, p->x, p->y + 1) : 1;
	return (n);
}

/*
** Locate the player position and store it.
** Replace the accessible areas around him by 'x'.
*/

int				locate_player(t_var *v, t_m_parse *p)
{
	int n;

	v->map_w = 0;
	n = 0;
	p->x = -1;
	while (p->m[++p->x])
	{
		p->y = -1;
		while (p->m[p->x][++p->y])
		{
			if (is_valid(p->m[p->x][p->y]) == 3)
			{
				if (p->x == 0 || p->y == 0 || p->x == v->map_h - 1
				|| p->y == v->map_w - 1)
					return (MAP_ERROR);
				init_player(v, p->x, p->y, p->m[p->x][p->y]);
				p->m[p->x][p->y] = p->r;
				n++;
				look_around(v, p, 1);
			}
		}
		v->map_w = p->y > v->map_w ? p->y : v->map_w;
	}
	return (n);
}

/*
** Replace the accessible area by 'x'.
*/

int				locate_accessible_area(t_var *v, t_m_parse *p)
{
	p->x = 0;
	while (p->m[p->x])
	{
		p->y = -1;
		while (p->m[p->x][++p->y])
		{
			if (p->m[p->x][p->y] == p->r)
			{
				if (p->x == 0 || p->y == 0 || p->x == v->map_h - 1
				|| p->y == v->map_w - 1)
					return (0);
				if (look_around(v, p, 1) > 0)
				{
					p->x = 0;
					p->y = -1;
				}
			}
			else if (!(is_valid(p->m[p->x][p->y])))
				return (0);
		}
		p->x++;
	}
	return (1);
}

/*
** Check for any errors outside the accessible area.
*/

int				check_contours(t_var *v, t_m_parse *p)
{
	p->x = -1;
	while (p->m[++p->x])
	{
		p->y = -1;
		while (p->m[p->x][++p->y])
		{
			if (is_valid(p->m[p->x][p->y]) == 4)
			{
				p->wntd = -1;
				if (look_around(v, p, 0) > 0)
					return (0);
				p->wntd = 1;
				if (look_around(v, p, 0) > 0)
					return (0);
			}
			else if (is_valid(p->m[p->x][p->y]) == 1)
				if (p->x == 0 || p->y == 0 || p->x == v->map_h - 1
				|| p->y == v->map_w - 1)
					return (0);
		}
	}
	return (1);
}
