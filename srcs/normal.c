/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 17:22:41 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/11 17:21:36 by jlucas-l         ###   ########.fr       */
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
