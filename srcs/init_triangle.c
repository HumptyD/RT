/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:54:33 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/02 17:57:23 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_triangle	init_triangle(void)
{
	t_triangle	triangle;

	triangle.a = (t_vector){0, 0, 0, 1};
	triangle.b = (t_vector){1, 0, 0, 1};
	triangle.c = (t_vector){0, 1, 0, 1};
	return (triangle);
}

void		triangle_size(t_triangle *triangle, double ab, double ac)
{
	triangle->b = vector_scalar_multiply(triangle->b, ab);
	triangle->c = vector_scalar_multiply(triangle->c, ac);
}

void		triangle_translation(t_triangle *triangle, t_vector position)
{
	t_matrix_4x4	m;

	m = translation_matrix(position);
	triangle->a = vector_matrix_multiply(triangle->a, m);
	triangle->b = vector_matrix_multiply(triangle->b, m);
	triangle->c = vector_matrix_multiply(triangle->c, m);
}

void		triangle_rotation(t_triangle *triangle, double x, double y, double z)
{
	t_matrix_4x4	m;

	m = matrix_multiply(x_rotation_matrix(x), y_rotation_matrix(y));
	m = matrix_multiply(m, z_rotation_matrix(z));
	triangle->a = vector_matrix_multiply(triangle->a, m);
	triangle->b = vector_matrix_multiply(triangle->b, m);
	triangle->c = vector_matrix_multiply(triangle->c, m);
}
