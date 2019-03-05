/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_foreach.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:21:39 by jlucas-l          #+#    #+#             */
/*   Updated: 2018/11/29 21:05:50 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_foreach(t_list *alst, void (*f)(void *, size_t))
{
	while (alst && f)
	{
		f(alst->content, alst->content_size);
		alst = alst->next;
	}
}
