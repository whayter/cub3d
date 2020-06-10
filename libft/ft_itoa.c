/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:02:40 by hwinston          #+#    #+#             */
/*   Updated: 2019/10/10 14:41:27 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long		ft_abs(long n)
{
	if (n >= 0)
		return (n);
	return (-n);
}

char			*ft_itoa(int n)
{
	unsigned long	nb;
	unsigned long	tmp;
	unsigned int	size;
	char			*res;

	nb = ft_abs((long)n);
	size = n <= 0 ? 1 : 0;
	tmp = nb * 10;
	while ((tmp /= 10) > 0)
		size++;
	if (!(res = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	res[size] = '\0';
	while (nb > 0)
	{
		res[--size] = nb % 10 + '0';
		nb /= 10;
	}
	n < 0 ? res[0] = '-' : 0;
	n == 0 ? res[0] = '0' : 0;
	return (res);
}
