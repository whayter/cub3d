/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:47:27 by hwinston          #+#    #+#             */
/*   Updated: 2019/10/25 14:41:09 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t		i;
	void		**obj;

	if (!(obj = (void **)malloc(sizeof(void *) * count * size)))
		return (NULL);
	i = -1;
	while (++i < count)
		obj[i] = 0;
	return (obj);
}
