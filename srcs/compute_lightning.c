/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lightning.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:31:07 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/04 17:13:52 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int			compute_point_light(t_render *render, t_light light,
									t_ray *l_ray, t_intersection inter)
{
	double	l_ray_len;

	l_ray->direction = vector_sub(inter.point, light.position);
	l_ray_len = vector_length(l_ray->direction);
	l_ray->direction = vector_normalize(l_ray->direction);
	l_ray->origin = light.position;
	if (!is_shadow(render, *l_ray, l_ray_len))
		return (1);
	return (0);
}

static int			compute_directed_light(t_render *render, t_light light,
										t_ray *l_ray, t_intersection inter)
{
	double	l_ray_len;

	l_ray->direction = vector_sub(inter.point, light.position);
	l_ray_len = vector_length(l_ray->direction);
	l_ray->direction = vector_normalize(l_ray->direction);
	l_ray->origin = light.position;
	if (acos(dot_product(l_ray->direction, light.direction)) < light.angle)
		if (!is_shadow(render, *l_ray, l_ray_len))
			return (1);
	return (0);
}

static	int			compute_parallel_light(t_render *render, t_light light,
										t_ray *l_ray, t_intersection inter)
{
	double	l_ray_len;

	l_ray_len = 1. / 0.;
	l_ray->direction = vector_scalar_multiply(light.direction, -1);
	l_ray->origin = vector_sum(inter.point,
			vector_scalar_multiply(l_ray->direction, 1e-8));
	if (!is_shadow(render, *l_ray, l_ray_len))
	{
		l_ray->direction = vector_scalar_multiply(l_ray->direction, -1);
		return (1);
	}
	return (0);
}

void		compute_lightning(t_render *render, t_intersection inter, t_ray ray, double *li)
{
	int		s;
	int		i;
	double	d;
	t_ray	l_ray;
	t_ray	l_m;

	normal_reverse(&inter.normal, ray.direction);
	li[0] = 0;
	li[1] = 0;
	s = 0;
	i = -1;
	while (++i < render->lights_nb)
	{
		if (render->lights[i].type == AMBIENT)
			li[0] += render->lights[i].intensity;
		if (render->lights[i].type == POINT)
			s = compute_point_light(render, render->lights[i], &l_ray, inter);
		if (render->lights[i].type == DIRECTED)
			s = compute_directed_light(render, render->lights[i], &l_ray, inter);
		if (render->lights[i].type == PARALLEL)
			s = compute_parallel_light(render, render->lights[i], &l_ray, inter);
		if (s)
		{
			li[0] += render->lights[i].intensity *
				fmax(0., dot_product(l_ray.direction, inter.normal));
			if (inter.primitive->material->shininess > -1)
			{
				l_m = reflected_ray(l_ray, inter);
				d = dot_product(l_m.direction, vector_scalar_multiply(ray.direction, -1));
				li[1] += render->lights[i].intensity *
					pow(fmax(0., d), inter.primitive->material->shininess);
			}
		}
	}
	li[0] = (li[0] > 1.) ? 1. : li[0];
	li[0] = (li[0] < 0.) ? 0. : li[0];
	li[1] = (li[1] > 1.) ? 1. : li[1];
	li[1] = (li[1] < 0.) ? 0. : li[1];
}
