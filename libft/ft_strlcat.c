/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:01:07 by hwinston          #+#    #+#             */
/*   Updated: 2019/10/09 17:02:19 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	dest_len;
	unsigned int	src_len;
	size_t			i;
	size_t			j;

	src_len = ft_strlen(src);
	dest_len = ft_strlen(dst);
	if (dstsize == 0)
		return (src_len);
	if (dstsize < dest_len)
		return (src_len + dstsize);
	i = 0;
	while (dst[i])
		i++;
	j = 0;
	while (i < dstsize - 1 && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (i < dstsize)
		dst[i] = '\0';
	return (src_len + dest_len);
}
