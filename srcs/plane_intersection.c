/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:07:25 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/02 19:03:33 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			light_plane_intersection(t_triangle plane, t_ray light_ray)
{
	t_vector		e[2];
	t_vector		v[3];
	double			det;

	e[0] = vector_sub(plane.b, plane.a);
	e[1] = vector_sub(plane.c, plane.a);
	v[0] = cross_product(light_ray.direction, e[1]);
	det = dot_product(e[0], v[0]);
	if (det < 1e-8 && det > -1e-8)
		return (0);
	det = 1 / det;
	v[1] = vector_sub(light_ray.origin, plane.a);
	v[2] = cross_product(v[1], e[0]);
	return (dot_product(e[1], v[2]) * det);
}

void			get_normal_plane(t_intersection *res,
							t_ray ray, t_vector e1, t_vector e2)
{
	res->point = vector_sum(ray.origin,
			vector_scalar_multiply(ray.direction, res->z));
	res->normal = vector_normalize(cross_product(e1, e2));
}

t_intersection	plane_intersection(t_ray ray, t_triangle plane)
{
	t_vector		e[2];
	t_vector		v[3];
	t_intersection	res;
	double			det;

	res = init_intersection();
	e[0] = vector_sub(plane.b, plane.a);
	e[1] = vector_sub(plane.c, plane.a);
	v[0] = cross_product(ray.direction, e[1]);
	det = dot_product(e[0], v[0]);
	if (det < 1e-8 && det > -1e-8)
		return (res);
	det = 1 / det;
	v[1] = vector_sub(ray.origin, plane.a);
	v[2] = cross_product(v[1], e[0]);
	res.z = dot_product(e[1], v[2]) * det;
	get_normal_plane(&res, ray, e[0], e[1]);
	res.u = fmod(dot_product(v[1], v[0]) * det, 1.);
	res.u < 0 ? res.u += 1 : 0;
	res.v = fmod(dot_product(ray.direction, v[2]) * det, 1.);
	res.v < 0 ? res.v += 1 : 0;
	return (res);
}
