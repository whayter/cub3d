/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:43:39 by hwinston          #+#    #+#             */
/*   Updated: 2019/10/25 15:47:01 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lnew(void *content)
{
	t_list		*elem;

	if (!(elem = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
		elem->content = NULL;
	else
		elem->content = content;
	elem->next = NULL;
	return (elem);
}

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new;
	t_list *new_start;

	if (!lst || !f || !del)
		return (NULL);
	if (!(new = ft_lnew(f(lst->content))))
	{
		ft_lstclear(&new, del);
		return (NULL);
	}
	new_start = new;
	lst = lst->next;
	while (lst)
	{
		if (!(new->next = ft_lnew(f(lst->content))))
		{
			ft_lstclear(&new_start, del);
			return (NULL);
		}
		lst = lst->next;
		new = new->next;
	}
	return (new_start);
}
