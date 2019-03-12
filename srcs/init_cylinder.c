/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 20:11:32 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/11 17:13:07 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_cylinder	init_cylinder(void)
{
	t_cylinder cylinder;

	cylinder.center = (t_vector){0, 0, 0, 1};
	cylinder.h_vec = (t_vector){0, 0, 1, 0};
	cylinder.r_vec = (t_vector){1, 0, 0, 0};
	cylinder.r = 10;
	cylinder.h = 30;
	return (cylinder);
}

void		cylinder_rotation(t_cylinder *cylinder,
								double x, double y, double z)
{
	t_matrix_4x4 m;

	m = matrix_multiply(x_rotation_matrix(x), y_rotation_matrix(y));
	m = matrix_multiply(m, z_rotation_matrix(z));
	cylinder->h_vec = vector_matrix_multiply(cylinder->h_vec, m);
	cylinder->r_vec = vector_matrix_multiply(cylinder->r_vec, m);
}
