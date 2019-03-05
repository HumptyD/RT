/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_unit_primitive.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:40:26 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/02/23 20:11:26 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	*get_unit_primitive(char type)
{
	void	*primitive;

	primitive = NULL;
	if (type == PLANE || type == TRIANGLE)
	{
		primitive = malloc(sizeof(t_triangle));
		*((t_triangle *)primitive) = init_triangle();
	}
	else if (type == CIRCLE)
	{
		primitive = malloc(sizeof(t_circle));
		*((t_circle *)primitive) = init_circle();
	}
	else if (type == SPHERE)
	{
		primitive = malloc(sizeof(t_sphere));
		*((t_sphere *)primitive) = init_sphere();
	}
	else if (type == CYLINDER)
	{
		primitive = malloc(sizeof(t_cylinder));
		*((t_cylinder *)primitive) = init_cylinder();
	}
	else if (type == CONE)
	{
		primitive = malloc(sizeof(t_cone));
		*((t_cone *)primitive) = init_cone();
	}
	return (primitive);
}
