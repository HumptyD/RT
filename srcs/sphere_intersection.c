/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 13:43:02 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/11 19:28:52 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		cut_sphere(t_intersection *res, t_sphere sphere,
								t_ray ray, double t0)
{
	res->point = vector_sum(ray.origin,
			vector_scalar_multiply(ray.direction, t0));
	res->normal = vector_normalize(vector_sub(res->point, sphere.center));
	if (sphere.cut_angle &&
			acos(dot_product(res->normal, sphere.cut_v)) > sphere.cut_angle)
		return (0);
	return (1);
}

double			light_sphere_intersection(t_sphere sphere, t_ray light_ray)
{
	t_vector		oc;
	t_quadric		q;
	double			t0;
	double			t1;
	t_intersection	res;

	oc = vector_sub(light_ray.origin, sphere.center);
	q.a = dot_product(light_ray.direction, light_ray.direction);
	q.b = 2 * dot_product(oc, light_ray.direction);
	q.c = dot_product(oc, oc) - sphere.r * sphere.r;
	if (!quadric_equation(q, &t0, &t1))
		return (0);
	if (t0 < 0 || !cut_sphere(&res, sphere, light_ray, t0))
		t0 = t1;
	if (t0 < 0 || !cut_sphere(&res, sphere, light_ray, t0))
		return (0);
	return (t0);
}

static void		uv_coords_sphere(t_intersection *res, t_sphere sphere)
{
	t_vector		cross;
	t_vector		v;
	t_matrix_4x4	m;

	res->v = vectors_angle(res->normal, sphere.latitude) / M_PI;
	cross = vector_normalize(cross_product(sphere.latitude, res->normal));
	m = arbitrary_rotation_matrix(cross,
			vectors_angle(sphere.latitude, res->normal) - (90 * M_PI / 180));
	v = vector_matrix_multiply(res->normal, m);
	res->u = vectors_angle(v, sphere.longitude) / M_PI;
}

t_intersection	sphere_intersection(t_ray ray, t_sphere sphere)
{
	t_vector		oc;
	t_quadric		q;
	double			t[2];
	t_intersection	res;

	res = init_intersection();
	oc = vector_sub(ray.origin, sphere.center);
	q.a = dot_product(ray.direction, ray.direction);
	q.b = 2 * dot_product(oc, ray.direction);
	q.c = dot_product(oc, oc) - sphere.r * sphere.r;
	if (!quadric_equation(q, &t[0], &t[1]))
		return (res);
	t[0] = (t[0] < 0 || !cut_sphere(&res, sphere, ray, t[0])) ? t[1] : t[0];
	if (t[0] < 0 || !cut_sphere(&res, sphere, ray, t[0]))
		return (res);
	res.z = t[0];
	res.point = vector_sum(ray.origin,
			vector_scalar_multiply(ray.direction, t[0]));
	res.normal = vector_normalize(vector_sub(res.point, sphere.center));
	uv_coords_sphere(&res, sphere);
	return (res);
}
