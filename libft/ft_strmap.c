/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 16:15:22 by jlucas-l          #+#    #+#             */
/*   Updated: 2018/11/25 16:42:01 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*res;
	size_t	i;

	if (s && f)
	{
		i = 0;
		if (!(res = (char *)ft_strnew((size_t)ft_strlen(s))))
			return (NULL);
		while (s[i])
		{
			res[i] = f(s[i]);
			i++;
		}
		return (res);
	}
	return (NULL);
}
