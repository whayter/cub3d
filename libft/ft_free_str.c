/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:18:58 by hwinston          #+#    #+#             */
/*   Updated: 2020/02/27 17:39:03 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_str(char **str, int r)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (r);
}
