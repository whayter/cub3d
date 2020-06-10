/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsndup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 09:28:15 by hwinston          #+#    #+#             */
/*   Updated: 2020/02/27 19:29:25 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsndup(char **strs, size_t size, int n)
{
	char	**new;
	int		i;

	if (!strs)
		return (NULL);
	if (!(new = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	i = -1;
	while (++i < n)
	{
		if (!(new[i] = ft_strdup(strs[i])))
		{
			ft_free_strs(new, size, 0);
			return (NULL);
		}
	}
	while ((size_t)i < size)
		new[i++] = 0;
	return (new);
}
