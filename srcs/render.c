/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:04:26 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/04 17:20:34 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_render(t_render *render)
{
	int	i;
	int color;
	t_vector tmp;

	ray_cast(render);
	i = -1;
	while (++i < render->w_width * render->w_height)
	{
		render->pixels[i] = ray_tracing(render, render->rays[i], 5);
		tmp = vector_scalar_multiply(render->pixels[i], 255);
		if (tmp.x > 255)
			tmp.x = 255.;
		if (tmp.y > 255)
			tmp.y = 255.;
		if (tmp.z > 255)
			tmp.z = 255.;
		color = ((int)tmp.x << 16 |(int)tmp.y << 8 | (int)tmp.z);
		set_pixel(render->sdl.surface, i % render->w_width,
				i / render->w_width, color);
	}
	SDL_UpdateWindowSurface(render->sdl.window);
}
