/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 17:12:08 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/11 16:25:15 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			light_circle_intersection(t_circle circle, t_ray ray)
{
	t_vector		e[2];
	t_vector		v[3];
	t_vector		point;
	double			det;
	double			z;

	e[0] = vector_sub(circle.plane.b, circle.plane.a);
	e[1] = vector_sub(circle.plane.c, circle.plane.a);
	v[0] = cross_product(ray.direction, e[1]);
	det = dot_product(e[0], v[0]);
	if (det < 1e-8 && det > -1e-8)
		return (0);
	det = 1 / det;
	v[1] = vector_sub(ray.origin, circle.plane.a);
	v[2] = cross_product(v[1], e[0]);
	z = dot_product(e[1], v[2]) * det;
	if (z == 0)
		return (0);
	point = vector_sum(ray.origin, vector_scalar_multiply(ray.direction, z));
	if (vector_length(vector_sub(point, circle.plane.a)) > circle.r)
		z = 0;
	return (z);
}

int				check_radius(t_intersection *res, t_ray ray, t_circle circle)
{
	res->point = vector_sum(ray.origin,
			vector_scalar_multiply(ray.direction, res->z));
	if (vector_length(vector_sub(res->point, circle.plane.a)) > circle.r)
	{
		res->z = 0;
		return (1);
	}
	return (0);
}

void			uv_coords_circle(t_intersection *res, t_circle circle)
{
	t_vector	cp;
	t_vector	ab;
	t_vector	ac;
	double		pr;
	double		len;

	cp = vector_sub(res->point, circle.plane.a);
	len = vector_length(cp);
	cp = vector_normalize(cp);
	ab = vector_normalize(vector_sub(circle.plane.b, circle.plane.a));
	ac = vector_normalize(vector_sub(circle.plane.c, circle.plane.a));
	pr = circle.r - dot_product(cp, ab) * len;
	res->v = pr / (circle.r * 2);
	pr = circle.r - dot_product(cp, ac) * len;
	res->u = pr / (circle.r * 2);
}

t_intersection	circle_intersection(t_ray ray, t_circle circle)
{
	t_vector		e[2];
	t_vector		v[3];
	t_intersection	res;
	double			det;

	res = init_intersection();
	e[0] = vector_sub(circle.plane.b, circle.plane.a);
	e[1] = vector_sub(circle.plane.c, circle.plane.a);
	v[0] = cross_product(ray.direction, e[1]);
	det = dot_product(e[0], v[0]);
	if (det < 1e-8 && det > -1e-8)
		return (res);
	det = 1 / det;
	v[1] = vector_sub(ray.origin, circle.plane.a);
	v[2] = cross_product(v[1], e[0]);
	res.z = dot_product(e[1], v[2]) * det;
	if (check_radius(&res, ray, circle))
		return (res);
	res.normal = vector_normalize(cross_product(e[0], e[1]));
	uv_coords_circle(&res, circle);
	return (res);
}
