/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:00:22 by hwinston          #+#    #+#             */
/*   Updated: 2019/10/09 16:58:17 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		i;
	char		*tmp;

	i = 0;
	if (c == '\0')
	{
		while (s[i])
			i++;
		return (&((char *)s)[i]);
	}
	tmp = NULL;
	while (s[i])
	{
		if (s[i] == (char)c)
			tmp = &((char *)s)[i];
		i++;
	}
	return (tmp);
}
