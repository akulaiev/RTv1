/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 13:38:19 by akulaiev          #+#    #+#             */
/*   Updated: 2017/12/01 13:38:20 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_lst;
	t_list *tmp;
	t_list *tmp1;

	if (!lst || !f)
		return (0);
	tmp1 = f(lst);
	new_lst = ft_lstnew(tmp1->content, tmp1->content_size);
	if (new_lst)
	{
		tmp = new_lst;
		lst = lst->next;
		while (lst)
		{
			tmp1 = f(lst);
			if (!(tmp->next = ft_lstnew(tmp1->content, tmp1->content_size)))
			{
				free(new_lst);
				return (0);
			}
			tmp = tmp->next;
			lst = lst->next;
		}
	}
	return (new_lst);
}
