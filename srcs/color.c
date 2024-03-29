/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:56:39 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/11 16:31:28 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector		init_vector_color(int color)
{
	t_vector	res;

	res.x = (double)(color >> 16 & 0xff);
	res.y = (double)(color >> 8 & 0xff);
	res.z = (double)(color & 0xff);
	res.w = 0.;
	return (res);
}

void			init_color(t_vector *color)
{
	color[0] = (t_vector){0, 0, 0, 0};
	color[1] = (t_vector){0, 0, 0, 0};
	color[2] = (t_vector){0, 0, 0, 0};
	color[3] = (t_vector){0, 0, 0, 0};
	color[4] = (t_vector){0, 0, 0, 0};
}

void			compute_specular_albedo(t_vector *color,
								double *li, t_intersection inter)
{
	if (inter.primitive->material->albedo)
		color[1] = vector_scalar_multiply(color[0],
				inter.primitive->material->albedo * li[0]);
	if (inter.primitive->material->specular)
		color[2] = vector_scalar_multiply(color[0],
				inter.primitive->material->specular * li[1]);
}

void			compute_reflection_refraction(t_vector *color,
												t_material *mat)
{
	if (mat->specular)
		color[3] = vector_scalar_multiply(color[3], mat->specular);
	if (mat->refraction)
		color[4] = vector_scalar_multiply(color[4], mat->refraction);
}

void			mix_color(t_vector *color)
{
	color[0] = vector_sum(color[1], color[2]);
	color[0] = vector_sum(color[0], color[3]);
	color[0] = vector_sum(color[0], color[4]);
}
