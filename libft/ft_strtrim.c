/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 13:12:06 by jlucas-l          #+#    #+#             */
/*   Updated: 2018/11/25 16:47:36 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

char			*ft_strtrim(char const *s)
{
	char	*res;
	char	*start;
	char	*end;
	size_t	i;
	size_t	len;

	res = NULL;
	if (s)
	{
		start = NULL;
		end = NULL;
		i = -1;
		len = ft_strlen(s) - 1;
		while (s[++i] && (start == NULL || end == NULL))
		{
			if (!is_space(s[i]) && start == NULL)
				start = (char *)s + i;
			if (!is_space(s[len - i]) && end == NULL)
				end = (char *)s + len - i + 1;
		}
		res = ft_strsub(s, (size_t)(start - s), (size_t)(end - start));
	}
	return (res);
}
