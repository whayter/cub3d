/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 19:39:48 by hwinston          #+#    #+#             */
/*   Updated: 2020/02/27 19:40:21 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;
	size_t	old_s;

	if (ptr == 0)
		return (malloc(size));
	old_s = sizeof(ptr);
	if (size <= old_s)
		return (ptr);
	new = malloc(size);
	ft_memcpy(ptr, new, old_s);
	free(ptr);
	return (new);
}
