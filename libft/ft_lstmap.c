/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:00:28 by ashalagi          #+#    #+#             */
/*   Updated: 2023/02/16 13:33:54 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	int		len;
	t_list	*res;

	if (!lst || !f)
		return (NULL);
	len = ft_lstsize(lst) - 1;
	if (!((f)(lst->content)))
		return (NULL);
	res = ft_lstnew((f)(lst->content));
	lst = lst->next;
	while (len)
	{
		if (!(f)(lst->content))
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		ft_lstadd_back(&res, ft_lstnew((f)(lst->content)));
		lst = lst->next;
		--len;
	}
	return (res);
}
