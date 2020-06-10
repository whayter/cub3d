/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 12:24:19 by hwinston          #+#    #+#             */
/*   Updated: 2020/04/30 09:30:43 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Check conformity of the texture path line.
*/

int		check_path_line(char *s)
{
	char	**t;

	if ((t = ft_split(s, ' ')) == NULL)
		return (MEM_ERROR);
	if (get_tab_size(t) != 2)
		return (ft_free_strs(t, -1, TEXT_ERROR));
	if (!(ft_strchr(t[1], '.')))
		return (ft_free_strs(t, -1, TEXT_ERROR));
	return (ft_free_strs(t, -1, 1));
}
