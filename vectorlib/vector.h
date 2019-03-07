/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:18:47 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/07 19:19:36 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
	double			w;
}					t_vector;

typedef struct		s_matrix_4x4
{
	double			matrix[4][4];
}					t_matrix_4x4;

typedef struct	s_triangle
{
	t_vector	a;
	t_vector	b;
	t_vector	c;
}				t_triangle;

typedef struct	s_sphere
{
	t_vector	center;
	t_vector	latitude;
	t_vector	longitude;
	t_vector	cut_v;
	double		cut_angle;
	double		r;
}				t_sphere;

typedef struct	s_cylinder
{
	t_vector	center;
	t_vector	h_vec;
	t_vector	r_vec;
	double		r;
	double		h;
}				t_cylinder;

typedef struct	s_circle
{
	t_triangle	plane;
	double		r;
}				t_circle;

typedef struct	s_cone
{
	t_vector	tip;
	t_vector	direction;
	t_vector	r_vec;
	double		angle;
	double		h;
}				t_cone;

t_vector			vector_normalize(t_vector v);
t_vector			vector_sub(t_vector a, t_vector b);
t_vector			vector_sum(t_vector a, t_vector b);
t_vector			cross_product(t_vector a, t_vector b);
double				dot_product(t_vector a, t_vector b);
double				vector_length(t_vector v1);
double				vectors_angle(t_vector a, t_vector b);
t_vector			vector_scalar_multiply(t_vector v, double n);
t_vector			vector_matrix_multiply(t_vector v, t_matrix_4x4 m);
t_vector			vector_vector_multiply(t_vector a, t_vector b);

t_matrix_4x4		matrix_multiply(t_matrix_4x4 a, t_matrix_4x4 b);
t_matrix_4x4		x_rotation_matrix(double alpha);
t_matrix_4x4		y_rotation_matrix(double alpha);
t_matrix_4x4		z_rotation_matrix(double alpha);
t_matrix_4x4		identity_matrix(void);
t_matrix_4x4		arbitrary_rotation_matrix(t_vector axis, double alpha);
t_matrix_4x4		change_basis(t_vector y, t_vector z, t_vector pos);
t_matrix_4x4		translation_matrix(t_vector v);

#endif
