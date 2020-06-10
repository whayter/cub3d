/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 09:03:40 by hwinston          #+#    #+#             */
/*   Updated: 2020/03/06 15:10:30 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsdup(char **strs, size_t size)
{
	size_t	i;
	char	**new;

	if (!strs)
		return (NULL);
	if (!(new = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	i = -1;
	while (++i < size)
	{
		if (!(new[i] = ft_strdup(strs[i])))
		{
			ft_free_strs(new, i, 0);
			return (NULL);
		}
	}
	new[i] = 0;
	return (new);
}
