/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:19:55 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/08 17:24:31 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	sdl_loop(t_render *render)
{
	int	quit;

	quit = 0;
	while (!quit)
	{
		while(SDL_PollEvent(&render->sdl.event))
		{
			if (render->sdl.event.type == SDL_QUIT)
				quit = 1;
			if (render->sdl.event.type == SDL_KEYDOWN)
				keyboard(render, &quit);
			if (render->sdl.event.type == SDL_WINDOWEVENT)
				if (render->sdl.event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					render->sdl.surface = SDL_GetWindowSurface(render->sdl.window);
					clear_surface(render->sdl.surface);
					render->w_width = render->sdl.event.window.data1;
					render->w_height = render->sdl.event.window.data2;
					render->cam.focus = render->w_width / tan(60 * M_PI / 180);
					free(render->rays);
					free(render->pixels);
					render->rays = (t_ray *)malloc(sizeof(t_ray) * render->w_width * render->w_height);
					render->pixels = (t_pixel *)malloc(sizeof(t_pixel) * render->w_width * render->w_height);
					init_pixels(render);
				}
		}
		if (render->trace_path)
			ft_render(render);
	}
}

void	init_sdl(t_render *render)
{
	render->w_width = 1280;
	render->w_height = 720;
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	render->sdl.window = SDL_CreateWindow(
			"test",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			render->w_width,
			render->w_height,
			SDL_WINDOW_RESIZABLE);
	render->sdl.surface = SDL_GetWindowSurface(render->sdl.window);
}

int		main(void)
{
	t_render	render;
	t_picture	pic;

	init_sdl(&render);
	init(&render);
	texture_reader("Terracotta_Tiles_002_basecolor.ppm", &pic);
	ft_render(&render);
	sdl_loop(&render);
	SDL_DestroyWindow(render.sdl.window);
	SDL_Quit();
	return (0);
}
