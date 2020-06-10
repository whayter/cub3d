/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:02:28 by hwinston          #+#    #+#             */
/*   Updated: 2020/03/02 10:37:43 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_free_tab(char **tab, size_t j)
{
	size_t i;

	i = 0;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static int		ft_count_words(char const *s, char c)
{
	size_t			i;
	size_t			count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char		*ft_scdup(char const *s1, char c)
{
	char			*s2;
	size_t			i;

	i = 0;
	while (s1[i] && s1[i] != c)
		i++;
	if (!(s2 = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != c)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char			**ft_split(char const *s, char c)
{
	size_t			i;
	size_t			j;
	size_t			words;
	char			**tab;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	i = 0;
	j = -1;
	while (++j < words)
	{
		while (s[i] && s[i] == c)
			i++;
		if (!(tab[j] = ft_scdup(&s[i], c)))
			return (ft_free_tab(tab, j));
		while (s[i] && s[i] != c)
			i++;
	}
	tab[j] = 0;
	return (tab);
}
