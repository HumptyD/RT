/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 20:43:18 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/01/31 20:49:23 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_get_color(int start, int end, double percent)
{
	int	r;
	int	g;
	int	b;

	if (start == end)
		return (start);
	r = ft_lerpi((start >> 16) & 0xFF, (end >> 16) & 0xFF, percent);
	g = ft_lerpi((start >> 8) & 0xFF, (end >> 8) & 0xFF, percent);
	b = ft_lerpi((start) & 0xFF, (end) & 0xFF, percent);
	return (r << 16 | g << 8 | b);
}
