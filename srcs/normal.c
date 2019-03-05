/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 17:22:41 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/05 18:48:12 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int						normal_id(t_intersection *inter)
{
	int	i;
	int	j;

	i = inter->u * inter->primitive->texture->picture->width;
	j = inter->v * inter->primitive->texture->picture->height;
	if (i == inter->primitive->texture->picture->width)
		i = inter->primitive->texture->picture->width - 1;
	if (j == inter->primitive->texture->picture->height)
		j = inter->primitive->texture->picture->height - 1;
	return (j * inter->primitive->texture->picture->width + i);

}

void					change_plane_basis(t_intersection *inter)
{
	t_matrix_4x4	m;
	t_vector		y;
	t_vector		normal;

	y = vector_normalize(vector_sub(((t_triangle *)inter->primitive->primitive)->c,
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

	y = vector_normalize(vector_sub(((t_circle *)inter->primitive->primitive)->plane.c,
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

	y = cross_product(((t_sphere *)inter->primitive->primitive)->longitude, inter->normal);
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

	y = cross_product(((t_cylinder *)inter->primitive->primitive)->h_vec, inter->normal);
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

	y = cross_product(((t_cone *)inter->primitive->primitive)->r_vec, inter->normal);
	y = vector_normalize(cross_product(y, inter->normal));
	m = change_basis(y, inter->normal, (t_vector){0, 0, 0, 1});
	normal = inter->primitive->texture->picture->normals[normal_id(inter)];
	inter->normal = vector_normalize(vector_matrix_multiply(normal, m));
}

void					get_pic_normal(t_intersection *inter)
{
	if (inter->primitive == NULL ||
			inter->primitive->texture->picture->normals == NULL)
		return ;
	else if (inter->primitive->type == TRIANGLE ||
		inter->primitive->type == PLANE)
		change_plane_basis(inter);
	else if (inter->primitive->type == CIRCLE)
		change_circle_basis(inter);
	else if (inter->primitive->type == SPHERE)
		change_sphere_basis(inter);
	else if (inter->primitive->type == CYLINDER)
		change_cylinder_basis(inter);
	else if (inter->primitive->type == CONE)
		change_cone_basis(inter);
}
