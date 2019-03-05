/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 18:59:32 by jlucas-l          #+#    #+#             */
/*   Updated: 2018/12/20 19:07:05 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ulltoa_base(unsigned long long n, int base, char *type)
{
	char				*res;
	int					len;
	unsigned long long	nb;

	nb = n;
	len = nb == 0 ? 1 : 0;
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
	return (res);
}
