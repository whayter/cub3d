/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:42:41 by hwinston          #+#    #+#             */
/*   Updated: 2019/10/25 15:41:57 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *li;
	t_list *tmp;

	if (!lst || !del)
		return ;
	li = *lst;
	while (li)
	{
		del(li->content);
		tmp = li->next;
		free(li);
		li = tmp;
	}
	*lst = NULL;
}
