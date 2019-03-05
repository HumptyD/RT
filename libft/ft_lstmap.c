/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:21:53 by jlucas-l          #+#    #+#             */
/*   Updated: 2018/11/28 16:34:07 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_freelst(t_list *lst)
{
	t_list *nobj;

	while (lst)
	{
		nobj = lst->next;
		free(lst->content);
		free(lst);
		lst = nobj;
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*obj;
	t_list	*temp;
	t_list	*new;

	if (!lst || !f)
		return (NULL);
	temp = f(lst);
	if (!(new = ft_lstnew(temp->content, temp->content_size)))
		return (NULL);
	obj = new;
	lst = lst->next;
	while (lst)
	{
		temp = f(lst);
		if (!(new->next = ft_lstnew(temp->content, temp->content_size)))
		{
			ft_freelst(obj);
			return (NULL);
		}
		new = new->next;
		lst = lst->next;
	}
	return (obj);
}
