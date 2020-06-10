/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:17:07 by hwinston          #+#    #+#             */
/*   Updated: 2020/04/28 18:54:23 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Get map resolution. return -1 in case of error.
*/

static int	get_res(t_var *v, char *s)
{
	char	**t;
	int		i;

	if (v->resx != 0)
		return (MUL_ERROR);
	if (!(ft_isspace(s[1])))
		return (RES_ERROR);
	if ((t = ft_split(s, ' ')) == NULL)
		return (MEM_ERROR);
	if ((i = get_tab_size(t)) != 3)
		return (ft_free_strs(t, i, RES_ERROR));
	if (!(ft_isnum_string(t[1])) || !(ft_isnum_string(t[2])))
		return (ft_free_strs(t, i, RES_ERROR));
	v->resx = ft_atoi(t[1]);
	v->resy = ft_atoi(t[2]);
	ft_free_strs(t, i, 0);
	if (v->resx < 20 || v->resy < 20)
		return (RES_ERROR);
	return (0);
}

/*
** Get floor and ceiling colors.
*/

static int	get_color(t_var *v, char *s)
{
	t_rgb	c;
	char	**t;
	int		i;

	if ((s[0] == 'F' && v->fl.f_clr != -1)
	|| (s[0] == 'C' && v->fl.c_clr != -1))
		return (MUL_ERROR);
	if (!(ft_isspace(s[1])))
		return (COLOR_ERROR);
	if ((t = ft_split(&s[2], ',')) == NULL)
		return (MEM_ERROR);
	if ((i = get_tab_size(t)) != 3 || ft_is_blank(t[0])
	|| ft_is_blank(t[1]) || ft_is_blank(t[2]))
		return (ft_free_strs(t, i, COLOR_ERROR));
	c.r = ft_atoi(t[0]);
	c.g = ft_atoi(t[1]);
	c.b = ft_atoi(t[2]);
	ft_free_strs(t, i, COLOR_ERROR);
	if ((c.clr = get_rgb(c.r, c.g, c.b)) == 0)
		return (COLOR_ERROR);
	if (s[0] == 'F')
		v->fl.f_clr = c.clr;
	else
		v->fl.c_clr = c.clr;
	return (0);
}

/*
** Look for every informations needed
** in each line of the .cub file.
*/

static int	parse_line(t_var *v, char *line)
{
	if (line[0] == 'R')
		return (get_res(v, line));
	else if (ft_strncmp(line, "NO ", 3) == 0)
		return (get_text_path(v, line, 0));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (get_text_path(v, line, 1));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (get_text_path(v, line, 2));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (get_text_path(v, line, 3));
	else if (ft_strncmp(line, "S ", 2) == 0)
		return (get_text_path(v, line, 4));
	else if (ft_strncmp(line, "F ", 2) == 0 && ft_strchr(line, '.'))
		return (get_text_path(v, line, 5));
	else if (line[0] == 'F')
		return (get_color(v, line));
	else if (ft_strncmp(line, "C ", 2) == 0 && ft_strchr(line, '.'))
		return (get_text_path(v, line, 6));
	else if (line[0] == 'C')
		return (get_color(v, line));
	else if (!ft_is_blank(line))
		return (MUL_ERROR);
	return (0);
}

/*
** Check for any missing informations.
*/

static int	got_all_info(t_var *v)
{
	int i;

	i = -1;
	while (++i < 5)
		if (v->tx.paths[i] == NULL)
			return (TEXT_MISSING);
	if (v->tx.fl_path == NULL && v->fl.f_clr == -1)
		return (TEXT_MISSING);
	if (v->tx.fl_path != NULL && v->fl.f_clr != -1)
		return (MUL_ERROR);
	if (v->tx.ce_path == NULL && v->fl.c_clr == -1)
		return (TEXT_MISSING);
	if (v->tx.ce_path != NULL && v->fl.c_clr != -1)
		return (MUL_ERROR);
	if (v->resx == 0 || v->resy == 0)
		return (RES_MISSING);
	return (0);
}

/*
** Informations parsing hub. Returns the index
** of the map' start line.
*/

int			get_info(t_var *v)
{
	int i;
	int r;

	if (!(v->tx.paths = malloc(sizeof(char *) * 5)))
		return (MEM_ERROR);
	i = -1;
	while (++i < 5)
		v->tx.paths[i] = NULL;
	i = -1;
	while (v->file[++i] != 0)
	{
		if (ft_isdigit(v->file[i][0]) || v->file[i][0] == ' ')
			break ;
		if ((r = parse_line(v, v->file[i])) < 0)
			return (r);
	}
	if ((r = got_all_info(v)) < 0)
		return (r);
	return (i);
}
