/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:28:24 by hwinston          #+#    #+#             */
/*   Updated: 2019/10/25 14:41:41 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_s;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		if (!(new_s = (char *)malloc(sizeof(char))))
			return (NULL);
		new_s[0] = '\0';
	}
	else
	{
		if (!(new_s = (char *)malloc(sizeof(char) * len + 1)))
			return (NULL);
		i = -1;
		while (++i < len && s[start + i])
			new_s[i] = s[start + i];
		new_s[i] = '\0';
	}
	return (new_s);
}
