/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:19:55 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/07 19:31:46 by jlucas-l         ###   ########.fr       */
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
