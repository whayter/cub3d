/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:11:56 by hwinston          #+#    #+#             */
/*   Updated: 2019/10/07 14:11:57 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_str_replace(char *s, char occ, char nocc)
{
	char	*new;
	int		i;

	if (!(new = malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	i = -1;
	while (s[++i])
	{
		if (s[i] == occ)
			new[i] = nocc;
		else
			new[i] = s[i];
	}
	new[i] = '\0';
	return (new);
}
