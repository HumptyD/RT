/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:56:39 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/02 18:52:29 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector		init_vector_color(int color)
{
	t_vector	res;

	res.x = (double)(color >> 16 & 0xff);
	res.y = (double)(color >> 8 & 0xff);
	res.z = (double)(color & 0xff);
	res.w = 0.;
	return (res);
}

t_vector		get_texture(t_intersection inter, t_texture texture)
{
	t_vector	color_vec;
	int			i;
	int			j;
	int			color;
	
	i = inter.u * texture.picture->width;
	j = inter.v * texture.picture->height;
	if (i == texture.picture->width)
		i = texture.picture->width - 1;
	if (j == texture.picture->height)
		j = texture.picture->height - 1;
	if (texture.a)
		i = texture.picture->width - i;
	if (texture.b)
		j = texture.picture->height - j;
	color = texture.picture->picture[j * texture.picture->width + i];
	color_vec = init_vector_color(color);
	color_vec = vector_scalar_multiply(color_vec, 1. / 255.);
	return (color_vec);
}

void		init_color(t_vector *color)
{
	color[0] = (t_vector){0,0,0,0};
	color[1] = (t_vector){0,0,0,0};
	color[2] = (t_vector){0,0,0,0};
	color[3] = (t_vector){0,0,0,0};
	color[4] = (t_vector){0,0,0,0};
}

void	compute_specular_albedo(t_vector *color, double *li, t_intersection inter)
{
	if (inter.primitive->material->albedo)
		color[1] = vector_scalar_multiply(color[0],
				inter.primitive->material->albedo * li[0]);
	if (inter.primitive->material->specular)
		color[2] = vector_scalar_multiply(color[0],
				inter.primitive->material->specular * li[1]);
}

void	compute_reflection_refraction(t_vector *color, t_material *mat)
{
	if (mat->specular)
		color[3] = vector_scalar_multiply(color[3], mat->specular);
	if (mat->refraction)
		color[4] = vector_scalar_multiply(color[4], mat->refraction);
}

void	mix_color(t_vector *color)
{
	color[0] = vector_sum(color[1], color[2]);
	color[0] = vector_sum(color[0], color[3]);
	color[0] = vector_sum(color[0], color[4]);
}
