/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 14:29:26 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/02/24 14:19:26 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "intersection.h"

static int		cone_limit(t_intersection *res,
					t_ray ray, t_cone cone, double t0)
{
	double		hyp;
	double		len;
	t_vector	tp;

	res->point = vector_sum(ray.origin,
			vector_scalar_multiply(ray.direction, t0));
	hyp = cone.h / cos(cone.angle);
	tp = vector_sub(res->point, cone.tip);
	len = vector_length(tp);
	if (len > hyp || dot_product(tp, cone.direction) < 0)
		return (1);
	return (0);
}

double			light_cone_intersection(t_cone cone, t_ray ray)
{
	t_quadric		q;
	t_cone_inter	inter;
	t_intersection	res;

	inter.dv = dot_product(ray.direction, cone.direction);
	inter.co = vector_sub(ray.origin, cone.tip);
	inter.cov = dot_product(inter.co, cone.direction);
	inter.cos_a = cos(cone.angle) * cos(cone.angle);
	q.a = inter.dv * inter.dv - inter.cos_a;
	q.b = 2 * (inter.dv * inter.cov - dot_product(ray.direction, inter.co)
			* inter.cos_a);
	q.c = inter.cov * inter.cov - dot_product(inter.co, inter.co) * inter.cos_a;
	if (!quadric_equation(q, &inter.t0, &inter.t1))
		return (0);
	if (inter.t0 < 0 || cone_limit(&res, ray, cone, inter.t0))
		inter.t0 = inter.t1;
	if (inter.t0 < 0 || cone_limit(&res, ray, cone, inter.t0))
		return (0);
	return (inter.t0);
}

static double	check_angle(t_vector r, t_vector cross, t_vector r_vec)
{
	double a1;
	double a2;

	a1 = acos(dot_product(r_vec, r));
	a2 = dot_product(cross, r);
	(a2 < 0) ? a1 = (M_PI * 2) - a1 : 0;
	return (a1);
}

static void		normal_uv_coords_cone(t_intersection *res, t_cone cone)
{
	t_vector	cross;
	t_vector	tp;
	t_vector	r;
	t_vector	h;
	double		cos_a;

	cross = vector_normalize(cross_product(cone.r_vec, cone.direction));
	tp = vector_sub(res->point, cone.tip);
	cos_a = cos(cone.angle);
	r = vector_normalize(vector_sub(
				vector_sum(cone.tip, vector_scalar_multiply(
						vector_normalize(tp), cone.h / cos_a)),
				vector_sum(cone.tip, vector_scalar_multiply(
						cone.direction, cone.h))));
	res->u = check_angle(r, cross, cone.r_vec) / (M_PI * 2);
	h = vector_sum(cone.tip, vector_scalar_multiply(
				cone.direction, vector_length(tp) * cos_a));
	res->v = vector_length(vector_sub(cone.tip, h)) / cone.h;
	h = vector_sum(cone.tip, vector_scalar_multiply(
				cone.direction, vector_length(tp) / cos_a));
	res->normal = vector_normalize(vector_sub(res->point, h));
}

t_intersection	cone_intersection(t_ray ray, t_cone cone)
{
	t_intersection	res;
	t_quadric		q;
	t_cone_inter	inter;

	res = init_intersection();
	inter.dv = dot_product(ray.direction, cone.direction);
	inter.co = vector_sub(ray.origin, cone.tip);
	inter.cov = dot_product(inter.co, cone.direction);
	inter.cos_a = cos(cone.angle) * cos(cone.angle);
	q.a = inter.dv * inter.dv - inter.cos_a;
	q.b = 2 * (inter.dv * inter.cov - dot_product(ray.direction, inter.co)
			* inter.cos_a);
	q.c = inter.cov * inter.cov - dot_product(inter.co, inter.co) * inter.cos_a;
	if (!quadric_equation(q, &inter.t0, &inter.t1))
		return (res);
	if (inter.t0 < 0 || cone_limit(&res, ray, cone, inter.t0))
		inter.t0 = inter.t1;
	if (inter.t0 < 0 || cone_limit(&res, ray, cone, inter.t0))
		return (res);
	res.z = inter.t0;
	normal_uv_coords_cone(&res, cone);
	return (res);
}
