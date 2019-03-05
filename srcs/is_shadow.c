/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:28:32 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/02 13:50:40 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double		light_intersection(t_primitive primitive, t_ray l_ray)
{
	double	z;

	z = 0;
	if (primitive.type == TRIANGLE)
		z = light_triangle_intersection(
				*((t_triangle *)primitive.primitive), l_ray);
	else if (primitive.type == PLANE)
		z = light_plane_intersection(
				*((t_triangle *)primitive.primitive), l_ray);
	else  if (primitive.type == CIRCLE)
		z = light_circle_intersection(
				*((t_circle *)primitive.primitive), l_ray);
	else if (primitive.type == SPHERE)
		z = light_sphere_intersection(
				*((t_sphere *)primitive.primitive), l_ray);
	else if (primitive.type == CYLINDER)
		z = light_cylinder_intersection(
				*((t_cylinder *)primitive.primitive), l_ray);
	else if (primitive.type == CONE)
		z = light_cone_intersection(
				*((t_cone *)primitive.primitive), l_ray);
	return (z);
}

int			is_shadow(t_render *render, t_ray l_ray, double l_ray_len)
{
	int		i;
	int		j;
	double		z;

	i = -1;
	while (++i < render->objects_nb)
	{
		j = -1;
		while (++j < render->objects[i].primitives_nb)
		{
			z = light_intersection(render->objects[i].primitives[j], l_ray);
			if (z > 0 && z < l_ray_len - 1e-8)
				return (1);
		}
	}
	return (0);
}
