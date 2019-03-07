/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tracing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:57:16 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/07 20:04:16 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	define_ray(t_ray *ray, t_intersection inter)
{
	double rand_n;

	rand_n = (double)rand() / RAND_MAX;
	if (rand_n < inter.primitive->material->albedo)
		*ray = random_ray(inter);
	else if (rand_n < inter.primitive->material->albedo +
			inter.primitive->material->specular)
		*ray = reflected_ray(*ray, inter);
	else if (rand_n < 1)
		*ray = refracted_ray(*ray, inter,
				inter.primitive->material->refractive_index);
}

static void	compute_color_signal(t_vector *color, double *li,
									t_intersection inter, t_vector *signal)
{
	color[0] = get_texture(inter, *inter.primitive->texture);
	color[1] = vector_sum(
			vector_scalar_multiply(color[0],
				inter.primitive->material->albedo * li[0]),
			vector_scalar_multiply(color[0],
				inter.primitive->material->specular * li[1]));
	color[1] = vector_vector_multiply(color[1], *signal);
	*signal = vector_vector_multiply(*signal, color[0]);
	color[2] = vector_sum(color[2], color[1]);
}

t_vector	path_tracing(t_render *render, t_ray ray, int depth)
{
	t_vector	signal;
	t_vector	color[3];
	t_intersection inter;
	double		li[2];

	color[2] = (t_vector){0, 0, 0, 0};
	signal = (t_vector){1, 1, 1, 0};
	while (depth--)
	{
		inter = get_closest_intersection(render, ray);
		if (inter.z > 0)
		{
			compute_lightning(render, inter, ray, li);
			compute_color_signal(color, li, inter, &signal);
			define_ray(&ray, inter);
		}
		else
			break ;
	}
	return (color[2]);
}
