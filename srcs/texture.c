/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:29:21 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/11 16:31:08 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
