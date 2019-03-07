/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:04:26 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/07 20:52:43 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		vector_to_color(t_pixel pixel)
{
	int			color;
	t_vector	tmp;
	
	tmp = vector_scalar_multiply(pixel.pixel, 1. / pixel.samples);
	tmp = vector_scalar_multiply(tmp, 255);
	if (tmp.x > 255)
		tmp.x = 255.;
	if (tmp.y > 255)
		tmp.y = 255.;
	if (tmp.z > 255)
		tmp.z = 255.;
	color = ((int)tmp.x << 16 |(int)tmp.y << 8 | (int)tmp.z);
	return (color);
}

void	fill_image(t_render *render)
{
	int	i;

	i = -1;
	while (++i < render->w_width * render->w_height)
		set_pixel(render->sdl.surface, i % render->w_width,
				i / render->w_width, vector_to_color(render->pixels[i]));
}

void	ray_lens_cast(t_render *render)
{
	int				i;
	int				area;
	t_vector		rand;
	t_matrix_4x4	rotation;

	i = -1;
	area = render->w_width * render->w_height;
	rotation = matrix_multiply(
			x_rotation_matrix(-render->cam.vert),
			z_rotation_matrix(-render->cam.hor));
	rand.x = (double)rand() / RAND_MAX * 2 - 1;
	rand.y = 0.;
	rand.z = (double)rand() / RAND_MAX * 2 - 1;
	rand.w = 0.;
	rand = vector_scalar_multiply(rand, render->cam.r);
	while (++i < area)
	{
		render->rays[i].origin = vector_sum(rand, render->cam.position);
		render->rays[i].direction =
			vector_matrix_multiply(vector_normalize((t_vector)
						{
						(i % render->w_width - render->w_width / 2),
						render->cam.focus,
						-(i / render->w_width - render->w_height / 2),
						0.
						}), rotation);
	}
}

void	ft_render(t_render *render)
{
	int	i;
	t_vector	tmp;

	if (!render->trace_path)
		ray_cast(render);
	else
		ray_lens_cast(render);
	i = -1;
	while (++i < render->w_width * render->w_height)
	{
		if (!render->trace_path)
		{
			render->pixels[i].pixel = ray_tracing(render, render->rays[i], 5);
			render->pixels[i].samples = 1;
		}
		else
		{
			tmp = path_tracing(render, render->rays[i], 10); 
			render->pixels[i].pixel = vector_sum(render->pixels[i].pixel, tmp);
			render->pixels[i].samples++;
		}
	}
	fill_image(render);
	SDL_UpdateWindowSurface(render->sdl.window);
}
