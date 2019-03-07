/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:46:07 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/06 17:15:21 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_sphere	init_sphere(void)
{
	t_sphere	sphere;

	sphere.center = (t_vector){0, 0, 0, 1};
	sphere.latitude = (t_vector){0, 0, 1, 0};
	sphere.longitude = (t_vector){1, 0, 0, 0};
	sphere.cut_v = (t_vector){0, 0, 0, 0};
	sphere.cut_angle = 0. * M_PI / 180;
	sphere.r = 10;
	return (sphere);
}

void	sphere_rotation(t_sphere *sphere, double x, double y, double z)
{
	t_matrix_4x4 m;

	m = matrix_multiply(x_rotation_matrix(x), y_rotation_matrix(y));
	m = matrix_multiply(m, z_rotation_matrix(z));
	sphere->latitude = vector_matrix_multiply(sphere->latitude, m);
	sphere->longitude = vector_matrix_multiply(sphere->longitude, m);
}
