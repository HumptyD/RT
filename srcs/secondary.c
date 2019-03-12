/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 17:29:52 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/11 19:28:09 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			normal_reverse(t_vector *normal, t_vector dir)
{
	if (dot_product(*normal, dir) < 0)
		*normal = vector_scalar_multiply(*normal, -1);
}

t_intersection	init_intersection(void)
{
	return ((t_intersection){0, 0, 0, (t_vector){0, 0, 0, 0},
		(t_vector){0, 0, 0, 0}, 0});
}

void			clear_surface(SDL_Surface *surface)
{
	ft_bzero(surface->pixels, surface->w * surface->h * 4);
}
