/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 19:46:53 by hwinston          #+#    #+#             */
/*   Updated: 2020/02/27 19:46:55 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_strs(char **strs, int size, int r)
{
	int i;

	i = -1;
	if (size == -1)
	{
		while (strs[++i] != 0)
			if (strs[i])
				ft_free_str(&strs[i], 0);
	}
	else
	{
		while (++i < size)
			if (strs[i])
				ft_free_str(&strs[i], 0);
	}
	if (strs)
	{
		free(strs);
		strs = NULL;
	}
	return (r);
}
