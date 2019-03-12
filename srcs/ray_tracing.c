/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 17:19:31 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/11 19:19:33 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		cast_ref_ray(t_ray *ref_ray, t_intersection inter, t_ray ray)
{
	if (inter.primitive->material->specular > 0)
		ref_ray[0] = reflected_ray(ray, inter);
	if (inter.primitive->material->refraction > 0)
		ref_ray[1] = refracted_ray(ray, inter,
						inter.primitive->material->refractive_index);
}

t_vector	ray_tracing(t_render *render, t_ray ray, int reflection)
{
	double			li[2];
	t_intersection	inter;
	t_vector		color[5];
	t_ray			ref_ray[2];

	init_color(color);
	inter = get_closest_intersection(render, ray);
	if (inter.z <= 0)
		return (color[0]);
	compute_lightning(render, inter, ray, li);
	color[0] = get_texture(inter, *inter.primitive->texture);
	compute_specular_albedo(color, li, inter);
	if (reflection)
	{
		cast_ref_ray(ref_ray, inter, ray);
		if (inter.primitive->material->specular > 0)
			color[3] = ray_tracing(render, ref_ray[0], reflection - 1);
		if (inter.primitive->material->refraction > 0)
			color[4] = ray_tracing(render, ref_ray[1], reflection - 1);
		compute_reflection_refraction(color, inter.primitive->material);
	}
	mix_color(color);
	return (color[0]);
}
