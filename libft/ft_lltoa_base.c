/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 17:14:50 by jlucas-l          #+#    #+#             */
/*   Updated: 2018/12/21 18:47:21 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lltoa_base(long long n, int base, char *type)
{
	char		*res;
	int			len;
	long long	nb;
	int			sign;

	res = NULL;
	nb = n;
	len = nb <= 0 ? 1 : 0;
	sign = n < 0 ? 1 : 0;
	while (nb)
	{
		nb /= base;
		len++;
	}
	res = ft_strnew(len);
	while (len--)
	{
		res[len] = (type ? type : "0123456789abcdef")[ABS(n % base)];
		n /= base;
	}
	res[0] = sign ? '-' : res[0];
	return (res);
}
