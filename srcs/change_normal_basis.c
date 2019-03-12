/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_normal_basis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 17:18:03 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/11 17:24:39 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void					change_plane_basis(t_intersection *inter)
{
	t_matrix_4x4	m;
	t_vector		y;
	t_vector		normal;

	y = vector_normalize(vector_sub(
				((t_triangle *)inter->primitive->primitive)->c,
				((t_triangle *)inter->primitive->primitive)->a));
	m = change_basis(y, inter->normal, (t_vector){0, 0, 0, 1});
	normal = inter->primitive->texture->picture->normals[normal_id(inter)];
	inter->normal = vector_normalize(vector_matrix_multiply(normal, m));
}

void					change_circle_basis(t_intersection *inter)
{
	t_matrix_4x4	m;
	t_vector		y;
	t_vector		normal;

	y = vector_normalize(vector_sub(
				((t_circle *)inter->primitive->primitive)->plane.c,
				((t_circle *)inter->primitive->primitive)->plane.a));
	m = change_basis(y, inter->normal, (t_vector){0, 0, 0, 1});
	normal = inter->primitive->texture->picture->normals[normal_id(inter)];
	inter->normal = vector_normalize(vector_matrix_multiply(normal, m));
}

void					change_sphere_basis(t_intersection *inter)
{
	t_matrix_4x4	m;
	t_vector		y;
	t_vector		normal;

	y = cross_product(
			((t_sphere *)inter->primitive->primitive)->latitude,
			inter->normal);
	y = vector_normalize(cross_product(y, inter->normal));
	m = change_basis(y, inter->normal, (t_vector){0, 0, 0, 1});
	normal = inter->primitive->texture->picture->normals[normal_id(inter)];
	inter->normal = vector_normalize(vector_matrix_multiply(normal, m));
}

void					change_cylinder_basis(t_intersection *inter)
{
	t_matrix_4x4	m;
	t_vector		y;
	t_vector		normal;

	y = cross_product(
			((t_cylinder *)inter->primitive->primitive)->h_vec,
			inter->normal);
	y = vector_normalize(cross_product(y, inter->normal));
	m = change_basis(y, inter->normal, (t_vector){0, 0, 0, 1});
	normal = inter->primitive->texture->picture->normals[normal_id(inter)];
	inter->normal = vector_normalize(vector_matrix_multiply(normal, m));
}

void					change_cone_basis(t_intersection *inter)
{
	t_matrix_4x4	m;
	t_vector		y;
	t_vector		normal;

	y = vector_normalize(vector_sub(
				((t_cone *)inter->primitive->primitive)->tip,
				inter->point));
	y = vector_normalize(cross_product(y, inter->normal));
	m = change_basis(y, inter->normal, (t_vector){0, 0, 0, 1});
	normal = inter->primitive->texture->picture->normals[normal_id(inter)];
	inter->normal = vector_normalize(vector_matrix_multiply(normal, m));
}
