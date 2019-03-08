/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_closest_intersection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:47:30 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/08 15:49:02 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_intersection	intersection(t_primitive primitive, t_ray ray)
{
	t_intersection	res;

	res = init_intersection();
	if (primitive.type == TRIANGLE)
		res = triangle_intersection(ray, *((t_triangle *)primitive.primitive));
	else if (primitive.type == PLANE)
		res = plane_intersection(ray, *((t_triangle *)primitive.primitive));
	else if (primitive.type == CIRCLE)
		res = circle_intersection(ray, *((t_circle *)primitive.primitive));
	else if (primitive.type == SPHERE)
		res = sphere_intersection(ray, *((t_sphere *)primitive.primitive));
	else if (primitive.type == CYLINDER)
		res = cylinder_intersection(ray, *((t_cylinder *)primitive.primitive));
	else if (primitive.type == CONE)
		res = cone_intersection(ray, *((t_cone *)primitive.primitive));
	return (res);	
}

t_intersection			get_closest_intersection(t_render *render, t_ray ray)
{
	t_intersection	res;
	t_intersection	temp;
	int				i;
	int				j;
	double			z;

	z = 1. / 0.;
	i = -1;
	res = init_intersection();
	while (++i < render->objects_nb)
	{
		j = -1;
		while (++j < render->objects[i].primitives_nb)
		{
			temp = intersection(render->objects[i].primitives[j], ray);
			if (temp.z > 0 && temp.z < z)
			{
				z = temp.z;
				res = temp;
				res.primitive = &(render->objects[i].primitives[j]);
			}
		}
	}
	get_pic_normal(&res);
	return (res);
}
