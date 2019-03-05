/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorted_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 18:07:39 by jlucas-l          #+#    #+#             */
/*   Updated: 2018/11/29 21:09:19 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_sorted_int(int *arr, int len, int (*f)(int, int))
{
	int	i;

	i = 0;
	if (!arr || !f)
		return (0);
	while (i < len - 1 && f)
	{
		if (f(arr[i], arr[i + 1]) > 0)
			return (0);
		i++;
	}
	return (1);
}
