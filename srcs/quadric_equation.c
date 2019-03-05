/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadric_equation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 14:41:32 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/02/13 16:36:03 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		quadric_equation(t_quadric q, double *t0, double *t1)
{
	double	d;

	d = q.b * q.b - 4 * q.a * q.c;
	if (d < 0)
		return (0);
	d = sqrt(d);
	*t0 = (-q.b - d) / (2 * q.a);
	*t1 = (-q.b + d) / (2 * q.a);
	if (*t0 > *t1)
		ft_swap_d(t0, t1);
	return (1);
}
