/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:21:16 by mescobar          #+#    #+#             */
/*   Updated: 2023/02/14 15:16:04 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*result_list;

	if (!lst || !f)
		return (NULL);
	result = ft_lstnew(f(lst->content));
	result_list = result;
	lst = lst->next;
	while (lst)
	{
		result->next = ft_lstnew(f(lst->content));
		if (lst->content == NULL)
		{
			ft_lstclear(&result_list, del);
			return (NULL);
		}
		lst = lst->next;
		result = result->next;
	}
	return (result_list);
}
