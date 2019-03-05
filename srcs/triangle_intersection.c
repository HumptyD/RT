/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 18:19:03 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/02 17:57:31 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			light_triangle_intersection(t_triangle triangle,
											t_ray light_ray)
{
	t_vector		e[2];
	t_vector		v[3];
	double			det;
	double			uv[2];

	e[0] = vector_sub(triangle.b, triangle.a);
	e[1] = vector_sub(triangle.c, triangle.a);
	v[0] = cross_product(light_ray.direction, e[1]);
	det = dot_product(e[0], v[0]);
	if (det < 1e-8 && det > -1e-8)
		return (0);
	det = 1 / det;
	v[1] = vector_sub(light_ray.origin, triangle.a);
	uv[0] = dot_product(v[1], v[0]) * det;
	if (uv[0] < 0 || uv[0] > 1)
		return (0);
	v[2] = cross_product(v[1], e[0]);
	uv[1] = dot_product(light_ray.direction, v[2]) * det;
	if (uv[1] < 0 || uv[0] + uv[1] > 1)
		return (0);
	return (dot_product(e[1], v[2]) * det);
}

void			get_normal_triangle(t_intersection *res,
						t_ray ray, t_vector e1, t_vector e2)
{
	res->point = vector_sum(ray.origin,
			vector_scalar_multiply(ray.direction, res->z));
	res->normal = vector_normalize(cross_product(e1, e2));
}

t_intersection	triangle_intersection(t_ray ray, t_triangle triangle)
{
	t_vector		e[2];
	t_vector		v[3];
	t_intersection	res;
	double			det;

	res = init_intersection();
	e[0] = vector_sub(triangle.b, triangle.a);
	e[1] = vector_sub(triangle.c, triangle.a);
	v[0] = cross_product(ray.direction, e[1]);
	det = dot_product(e[0], v[0]);
	if (det < 1e-8 && det > -1e-8)
		return (res);
	det = 1 / det;
	v[1] = vector_sub(ray.origin, triangle.a);
	res.u = dot_product(v[1], v[0]) * det;
	if (res.u < 0 || res.u > 1)
		return (res);
	v[2] = cross_product(v[1], e[0]);
	res.v = dot_product(ray.direction, v[2]) * det;
	if (res.v < 0 || res.u + res.v > 1)
		return (res);
	res.z = dot_product(e[1], v[2]) * det;
	get_normal_triangle(&res, ray, e[0], e[1]);
	return (res);
}
