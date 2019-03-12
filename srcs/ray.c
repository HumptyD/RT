/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:49:26 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/11 18:47:48 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray		random_ray(t_intersection inter)
{
	t_ray	random_ray;

	random_ray.direction.x = (double)rand() / RAND_MAX - 0.5;
	random_ray.direction.y = (double)rand() / RAND_MAX - 0.5;
	random_ray.direction.z = (double)rand() / RAND_MAX - 0.5;
	random_ray.direction.w = 0.;
	random_ray.direction = vector_normalize(random_ray.direction);
	if (dot_product(random_ray.direction, inter.normal) < 0)
		random_ray.direction = vector_scalar_multiply(random_ray.direction, -1);
	random_ray.origin = vector_sum(inter.point,
							vector_scalar_multiply(random_ray.direction, 1e-8));
	return (random_ray);
}

t_ray		refracted_ray(t_ray ray, t_intersection inter, double refr_index)
{
	double		cosi;
	double		eta[2];
	double		index[2];
	t_ray		refr_ray;

	cosi = -dot_product(ray.direction, inter.normal);
	eta[0] = 1.;
	eta[1] = refr_index;
	if (cosi < 0)
	{
		cosi = -cosi;
		ft_swap_d(&eta[0], &eta[1]);
		inter.normal = vector_scalar_multiply(inter.normal, -1);
	}
	index[0] = eta[0] / eta[1];
	index[1] = 1 - index[0] * index[0] * (1 - cosi * cosi);
	refr_ray.direction = (index[1] < 0) ?
		refr_ray.direction = (t_vector){0, 0, 0, 0} :
		vector_normalize(vector_sum(
					vector_scalar_multiply(ray.direction, index[0]),
					vector_scalar_multiply(inter.normal,
						index[0] * cosi - sqrt(index[1]))));
	refr_ray.origin = vector_sum(inter.point,
			vector_scalar_multiply(refr_ray.direction, 1e-8));
	return (refr_ray);
}

t_ray		reflected_ray(t_ray ray, t_intersection inter)
{
	t_ray	refl_ray;

	refl_ray.direction = vector_normalize(vector_sub(ray.direction,
				vector_scalar_multiply(inter.normal,
					2 * dot_product(ray.direction, inter.normal))));
	refl_ray.origin = vector_sum(inter.point,
			vector_scalar_multiply(refl_ray.direction, 1e-8));
	return (refl_ray);
}

void		ray_cast(t_render *render)
{
	int				i;
	int				area;
	t_matrix_4x4	rotation;

	i = -1;
	area = render->w_width * render->w_height;
	rotation = matrix_multiply(
			x_rotation_matrix(-render->cam.vert),
			z_rotation_matrix(-render->cam.hor));
	while (++i < area)
	{
		render->rays[i].origin = render->cam.position;
		render->rays[i].direction =
			vector_matrix_multiply(vector_normalize((t_vector)
						{
						(i % render->w_width - render->w_width / 2),
						render->cam.focus,
						-(i / render->w_width - render->w_height / 2),
						0.
						}), rotation);
	}
}
