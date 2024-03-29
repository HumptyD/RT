/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_vector_by_x_z.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 15:25:07 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/02/08 12:13:13 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	rotation_vector_by_x_z(t_vector v, double x, double z)
{
	v = vector_matrix_multiply(v, matrix_multiply(
		x_rotation_matrix(-z), z_rotation_matrix(-x)));
	return (v);
}
