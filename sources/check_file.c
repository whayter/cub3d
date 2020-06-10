/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:16:52 by hwinston          #+#    #+#             */
/*   Updated: 2020/04/30 09:00:13 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Read the file and store it in v->file.
** Return an error code if something goes wrong.
*/

int				rd_file(t_var *v, int fd)
{
	int		i;
	int		r;
	char	**tmp;

	if (!(v->file = (char **)malloc(sizeof(char *))))
		return (MEM_ERROR);
	i = -1;
	while ((r = get_next_line(fd, &v->file[++i])) > 0)
	{
		if (!(tmp = ft_strsdup(v->file, i + 1)))
			return (ft_free_strs(v->file, i + 1, MEM_ERROR));
		ft_free_strs(v->file, i + 1, 0);
		if (!(v->file = ft_strsndup(tmp, i + 2, i + 1)))
			return (ft_free_strs(tmp, i + 2, MEM_ERROR));
		ft_free_strs(tmp, i + 2, 0);
	}
	if (r == -1)
		return (ft_free_strs(v->file, i + 2, READ_ERROR));
	v->file[i] = 0;
	return (0);
}

static int		get_map_2(t_var *v, int i)
{
	if (v->file[i][v->j] == '2')
	{
		v->sp.s[v->sprite].x = v->x + 0.5;
		v->sp.s[v->sprite++].y = v->y + 1.5;
	}
	if (v->file[i][v->j] == ' ')
		v->map[v->x][++v->y] = '1';
	else if (is_valid(v->file[i][v->j]) == 3)
		v->map[v->x][++v->y] = '0';
	else
		v->map[v->x][++v->y] = v->file[i][v->j];
	return (0);
}

/*
** Get map from file and store it int v->map.
*/

static int		get_map(t_var *v, int i)
{
	v->x = -1;
	v->sprite = 0;
	while (v->file[i] != 0)
	{
		if (!(v->map[++v->x] = ft_memalloc(v->map_w + 1)))
			return (MEM_ERROR);
		v->j = -1;
		v->y = -1;
		while (v->file[i][++v->j])
			get_map_2(v, i);
		while (v->y < v->map_w)
			v->map[v->x][v->y++] = '1';
		v->map[v->x][v->y] = '\0';
		i++;
	}
	v->map[++v->x] = 0;
	return (0);
}

/*
** File parsing hub. Store every
** informations needed.
*/

int				check_file(t_var *v, char *file)
{
	int		fd;
	int		r;

	if (ft_strcmp(ft_strrchr(file, '.'), ".cub") != 0)
		return (FILENAME_ERROR);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (READ_ERROR);
	if ((r = rd_file(v, fd) < 0))
		return (r);
	close(fd);
	v_init(v);
	if ((v->m_strt = get_info(v)) < 0)
		return (partial_free(v, v->m_strt));
	if ((r = check_map(v)) < 0)
		return (partial_free(v, r));
	if (!(v->sp.s = malloc(sizeof(t_spos) * v->sp.n_sp)))
		return (MEM_ERROR);
	if (!(v->map = malloc(sizeof(char *) * (v->map_h + 1))))
	{
		free(v->sp.s);
		return (MEM_ERROR);
	}
	if ((r = get_map(v, v->m_strt)) < 0)
		return (partial_free(v, r));
	return (ft_free_strs(v->file, -1, 0));
}
