/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 18:30:54 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/02/23 14:41:26 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				cylinder_limit(t_intersection *res,
					t_ray ray, t_cylinder cylinder, double t0)
{
	double		k;
	double		len;
	double		hyp;
	t_vector	v_center;

	k = cylinder.h / 2;
	hyp = sqrt(cylinder.r * cylinder.r + k * k);
	res->point = vector_sum(ray.origin,
			vector_scalar_multiply(ray.direction, t0));
	v_center = vector_sum(cylinder.center,
			vector_scalar_multiply(cylinder.h_vec, k));
	len = vector_length(vector_sub(res->point, v_center));
	if (len > hyp)
		return (1);
	res->z = t0;
	return (0);
}

double			light_cylinder_intersection(t_cylinder cylinder, t_ray ray)
{
	t_vector		v[3];
	t_quadric		q;
	t_intersection	res;
	double			t0;
	double			t1;

	v[0] = cross_product(ray.direction, cylinder.h_vec);
	v[1] = vector_sub(ray.origin, cylinder.center);
	v[2] = cross_product(v[1], cylinder.h_vec);
	q.a = dot_product(v[0], v[0]);
	q.b = 2 * dot_product(v[0], v[2]);
	q.c = dot_product(v[2], v[2]) - cylinder.r * cylinder.r;
	if (!quadric_equation(q, &t0, &t1))
		return (0);
	if (t0 < 0 || cylinder_limit(&res, ray, cylinder, t0))
		t0 = t1;
	if (t0 < 0 || cylinder_limit(&res, ray, cylinder, t0))
		return (0);
	return (t0);
}

void			uv_coords_cylinder(t_intersection *res, t_cylinder cylinder)
{
	t_vector		cp;
	double			pr_len;

	cp = vector_sub(res->point, cylinder.center);
	pr_len = vector_length(cp) *
			dot_product(cylinder.h_vec, vector_normalize(cp));
	res->v = pr_len / cylinder.h;
	res->u = (dot_product(res->normal, cylinder.r_vec) + 1) / 2;
}

static void			get_normal_cylinder(t_intersection *res,
						t_cylinder cylinder)
{
	t_vector	v1;
	t_vector	v2;

	v1 = vector_sub(res->point, cylinder.center);
	v2 = cross_product(v1, cylinder.h_vec);
	res->normal = vector_normalize(cross_product(v2, cylinder.h_vec));
}

t_intersection	cylinder_intersection(t_ray ray, t_cylinder cylinder)
{
	t_intersection	res;
	t_quadric		q;
	double			t0;
	double			t1;
	t_vector		v[3];

	res = init_intersection();
	v[0] = cross_product(ray.direction, cylinder.h_vec);
	v[1] = vector_sub(ray.origin, cylinder.center);
	v[2] = cross_product(v[1], cylinder.h_vec);
	q.a = dot_product(v[0], v[0]);
	q.b = 2 * dot_product(v[0], v[2]);
	q.c = dot_product(v[2], v[2]) - cylinder.r * cylinder.r;
	if (!quadric_equation(q, &t0, &t1))
		return (res);
	if (t0 < 0 || cylinder_limit(&res, ray, cylinder, t0))
		t0 = t1;
	if (t0 < 0 || cylinder_limit(&res, ray, cylinder, t0))
		return (res);
	get_normal_cylinder(&res, cylinder);
	uv_coords_cylinder(&res, cylinder);
	return (res);
}
