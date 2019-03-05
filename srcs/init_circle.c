/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 19:26:30 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/02/23 20:07:10 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_circle	init_circle(void)
{
	t_circle	circle;

	circle.plane = init_triangle();
	circle.r = 10;
	return (circle);
}
