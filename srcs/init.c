/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:24:23 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/08 17:37:50 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_pixels(t_render *render)
{
	int	i;

	i = -1;
	while (++i < render->w_width * render->w_height)
	{
		render->pixels[i].pixel = (t_vector){0, 0, 0, 0};
		render->pixels[i].samples = 0;
	}
}

void	init(t_render *render)
{

	render->cam.position = (t_vector){0, -70, 35, 1};
	render->cam.hor = 0. * M_PI / 180;
	render->cam.vert = -23. * M_PI / 180;
	render->cam.focus = render->w_width / tan(60 * M_PI / 180);
	render->cam.r = 0.1;

	render->trace_path = 1;

	render->lights_nb = 1;
	render->objects_nb = 1;
	render->materials_nb = 3;
	render->textures_nb = 5;
	render->pictures_nb = 5;

	render->rays = (t_ray *)malloc(sizeof(t_ray) * render->w_width * render->w_height);
	render->lights = (t_light *)malloc(sizeof(t_light) * render->lights_nb);
	render->objects = (t_object *)malloc(sizeof(t_object) * render->objects_nb);
	render->materials = (t_material *)malloc(sizeof(t_material) * render->materials_nb);
	render->pixels = (t_pixel *)malloc(sizeof(t_pixel) * render->w_width * render->w_height);
	init_pixels(render);
	render->textures = (t_texture *)malloc(sizeof(t_texture) * render->textures_nb);
	render->pictures = (t_picture *)malloc(sizeof(t_picture) * render->pictures_nb);

	render->materials[0].albedo = 0.7;
	render->materials[0].specular = 0.3;
	render->materials[0].shininess = 500.;
	render->materials[0].refraction = 0;
	render->materials[0].refractive_index = 0;
	render->materials[0].emittance = 0.;
	render->materials[0].intensity = 0.;

	render->materials[1].albedo = 0;
	render->materials[1].specular = 0;
	render->materials[1].shininess = 0.;
	render->materials[1].refraction = 0;
	render->materials[1].refractive_index = 0;
	render->materials[1].emittance = 1;
	render->materials[1].intensity = 1;

	render->materials[2].albedo = 1;
	render->materials[2].specular = 0;
	render->materials[2].shininess = -1.;
	render->materials[2].refraction = 0;
	render->materials[2].refractive_index = 0;
	render->materials[2].emittance = 0.;
	render->materials[2].intensity = 0.;

	render->pictures[0].width = 1;
	render->pictures[0].height = 1;
	render->pictures[0].picture = (int *)malloc(sizeof(int) * 1);
	render->pictures[0].normals = NULL;
	render->pictures[0].picture[0] = 0xffffff;

	render->pictures[1].width = 1;
	render->pictures[1].height = 1;
	render->pictures[1].picture = (int *)malloc(sizeof(int) * 1);
	render->pictures[1].normals = NULL;
	render->pictures[1].picture[0] = 0xffffff;

	render->pictures[2].width = 1;
	render->pictures[2].height = 1;
	render->pictures[2].picture = (int *)malloc(sizeof(int) * 1);
	render->pictures[2].normals = NULL;
	render->pictures[2].picture[0] = 0xffd700; //gold

	render->pictures[3].width = 1;
	render->pictures[3].height = 1;
	render->pictures[3].picture = (int *)malloc(sizeof(int) * 1);
	render->pictures[3].normals = NULL;
	render->pictures[3].picture[0] = 0xc0c0c0; //silver

	render->pictures[4].width = 1;
	render->pictures[4].height = 1;
	render->pictures[4].picture = (int *)malloc(sizeof(int) * 1);
	render->pictures[4].normals = NULL;
	render->pictures[4].picture[0] = 0x00cfff; //blue

	render->textures[0].picture = &render->pictures[0];
	render->textures[0].a = 0;
	render->textures[0].b = 0;

	render->textures[1].picture = &render->pictures[1];
	render->textures[1].a = 0;
	render->textures[1].b = 0;

	render->textures[2].picture = &render->pictures[2];
	render->textures[2].a = 0;
	render->textures[2].b = 0;

	render->textures[3].picture = &render->pictures[3];
	render->textures[3].a = 0;
	render->textures[3].b = 0;

	render->textures[4].picture = &render->pictures[4];
	render->textures[4].a = 0;
	render->textures[4].b = 0;

//	texture_reader("bridge.ppm", &render->pictures[2]);
//	normal_reader("bridge_normal.ppm", &render->pictures[2]);

	render->lights[0].position = (t_vector){0, -70, -150, 1};
	render->lights[0].intensity = 1;
	render->lights[0].type = POINT;

	//	render->lights[1].position = (t_vector){0, 70, -80, 1};
	//	render->lights[1].intensity = 1;
	//	render->lights[1].type = POINT;

	//	render->lights[0].position = (t_vector){0, 0, 150, 1};
	//	render->lights[0].direction = vector_normalize((t_vector){0, 0, -1, 0});
	//	m = matrix_multiply(y_rotation_matrix(0 * M_PI / 180), z_rotation_matrix(0 * M_PI / 180));
	//	m = matrix_multiply(x_rotation_matrix(0 * M_PI / 180), m);
	//	render->lights[0].direction = vector_matrix_multiply(render->lights[0].direction, m);
	//	render->lights[0].angle = 30. * M_PI / 180;
	//	render->lights[0].intensity = 1;
	//	render->lights[0].type = DIRECTED;

	//	render->lights[0].direction = vector_normalize((t_vector){0, 0, -1, 0});
	//	m = matrix_multiply(y_rotation_matrix(30 * M_PI / 180), z_rotation_matrix(0 * M_PI / 180));
	//	m = matrix_multiply(x_rotation_matrix(0 * M_PI / 180), m);
	//	render->lights[0].direction = vector_matrix_multiply(render->lights[0].direction, m);
	//	render->lights[0].intensity = 1;
	//	render->lights[0].type = PARALLEL;

	render->objects[0].primitives_nb = 5;
	render->objects[0].primitives = (t_primitive *)malloc(sizeof(t_primitive)
			* render->objects[0].primitives_nb);

	render->objects[0].primitives[0].type = SPHERE;
	render->objects[0].primitives[0].primitive = get_unit_primitive(
			render->objects[0].primitives[0].type);
	render->objects[0].primitives[0].material = &render->materials[0];
	sphere_rotation((t_sphere *)render->objects[0].primitives[0].primitive,
			0. * M_PI / 180, 0. * M_PI / 180, 0. * M_PI / 180);
	((t_sphere *)render->objects[0].primitives[0].primitive)->center = (t_vector){21, 0, 10, 1};
	render->objects[0].primitives[0].texture = &render->textures[3];

	render->objects[0].primitives[1].type = SPHERE;
	render->objects[0].primitives[1].primitive = get_unit_primitive(
			render->objects[0].primitives[1].type);
	render->objects[0].primitives[1].material = &render->materials[0];
	sphere_rotation((t_sphere *)render->objects[0].primitives[1].primitive,
			0. * M_PI / 180, 0. * M_PI / 180, 0. * M_PI / 180);
	((t_sphere *)render->objects[0].primitives[1].primitive)->center = (t_vector){0, 0, 10, 1};
	//	((t_sphere *)render->objects[0].primitives[1].primitive)->cut_v = vector_normalize((t_vector){1, 0, 0, 0});
	//	((t_sphere *)render->objects[0].primitives[1].primitive)->cut_angle = 90 * M_PI / 180;
	render->objects[0].primitives[1].texture = &render->textures[2];


	render->objects[0].primitives[2].type = PLANE;
	render->objects[0].primitives[2].primitive = get_unit_primitive(
			render->objects[0].primitives[2].type);
	render->objects[0].primitives[2].material = &render->materials[2];
	triangle_size((t_triangle *)render->objects[0].primitives[2].primitive, 100, 100);
	triangle_rotation((t_triangle *)render->objects[0].primitives[2].primitive,
			0 * M_PI / 180, 0 * M_PI / 180, 0 * M_PI / 180);
	render->objects[0].primitives[2].texture = &render->textures[1];

	render->objects[0].primitives[3].type = CIRCLE;
	render->objects[0].primitives[3].primitive = get_unit_primitive(
	render->objects[0].primitives[3].type);
	render->objects[0].primitives[3].material = &render->materials[1];
	((t_circle *)render->objects[0].primitives[3].primitive)->r = 20000;
	triangle_rotation(&((t_circle *)render->objects[0].primitives[3].primitive)->plane,
	0 * M_PI / 180, 0 * M_PI / 180, 0 * M_PI / 180);
	triangle_translation(&((t_circle *)render->objects[0].primitives[3].primitive)->plane,
	(t_vector){0, 0, 5000, 1});
	render->objects[0].primitives[3].texture = &render->textures[0];

	render->objects[0].primitives[4].type = SPHERE;
	render->objects[0].primitives[4].primitive = get_unit_primitive(
			render->objects[0].primitives[4].type);
	render->objects[0].primitives[4].material = &render->materials[0];
	sphere_rotation((t_sphere *)render->objects[0].primitives[4].primitive,
			0. * M_PI / 180, 0. * M_PI / 180, 0. * M_PI / 180);
	((t_sphere *)render->objects[0].primitives[4].primitive)->center = (t_vector){-21, 0, 10, 1};
	render->objects[0].primitives[4].texture = &render->textures[4];
/*
	render->objects[0].primitives[3].type = SPHERE;
	render->objects[0].primitives[3].primitive = get_unit_primitive(
		render->objects[0].primitives[3].type);
	render->objects[0].primitives[3].material = &render->materials[1];
	((t_sphere *)render->objects[0].primitives[3].primitive)->center = (t_vector){0, 0, 0, 1};
	((t_sphere *)render->objects[0].primitives[3].primitive)->r = 5000;
	render->objects[0].primitives[3].texture = &render->textures[0];
*/

	/*
	   render->objects[0].primitives[3].type = TRIANGLE;
	   render->objects[0].primitives[3].primitive = get_unit_primitive(
	   render->objects[0].primitives[3].type);
	   render->objects[0].primitives[3].material = &render->materials[1];
	   triangle_size((t_triangle *)render->objects[0].primitives[3].primitive, 20, 20);
	   triangle_rotation((t_triangle *)render->objects[0].primitives[3].primitive,
	   -70 * M_PI / 180, 0 * M_PI / 180, 0 * M_PI / 180);
	   triangle_translation((t_triangle *)render->objects[0].primitives[3].primitive,
	   (t_vector){-40, 0, 40, 1});
	   render->objects[0].primitives[3].texture = &render->textures[2];

	   render->objects[0].primitives[4].type = CIRCLE;
	   render->objects[0].primitives[4].primitive = get_unit_primitive(
	   render->objects[0].primitives[4].type);
	   render->objects[0].primitives[4].material = &render->materials[1];
	   ((t_circle *)render->objects[0].primitives[4].primitive)->r = 10;
	   triangle_rotation(&((t_circle *)render->objects[0].primitives[4].primitive)->plane,
	   -70 * M_PI / 180, 0 * M_PI / 180, 0 * M_PI / 180);
	   triangle_translation(&((t_circle *)render->objects[0].primitives[4].primitive)->plane,
	   (t_vector){0, 0, 40, 1});
	   render->objects[0].primitives[4].texture = &render->textures[2];


	   render->objects[0].primitives[5].type = CYLINDER;
	   render->objects[0].primitives[5].primitive = get_unit_primitive(
	   render->objects[0].primitives[5].type);
	   render->objects[0].primitives[5].material = &render->materials[1];
	   ((t_cylinder *)render->objects[0].primitives[5].primitive)->center = (t_vector){15, 0, 50, 1};	
	   cylinder_rotation((t_cylinder *)render->objects[0].primitives[5].primitive,
	   0 * M_PI / 180, -90 * M_PI / 180, 0 * M_PI / 180);
	   render->objects[0].primitives[5].texture = &render->textures[2];


	   render->objects[0].primitives[6].type = CONE;
	   render->objects[0].primitives[6].primitive = get_unit_primitive(
	   render->objects[0].primitives[6].type);
	   render->objects[0].primitives[6].material = &render->materials[1];
	   ((t_cone *)render->objects[0].primitives[6].primitive)->tip = (t_vector){-50, 0, 40, 1};	
	   cone_rotation((t_cone *)render->objects[0].primitives[6].primitive,
	   -40 * M_PI / 180, 0 * M_PI / 180, 0 * M_PI / 180);
	   render->objects[0].primitives[6].texture = &render->textures[2];
	   */
}













/*
   void	init(t_render *render)
   {
   render->cam.position = (t_vector){-10, -300, 60, 1};
   render->cam.hor = 0. * M_PI / 180;
   render->cam.vert = 0. * M_PI / 180;
   render->cam.focus = 1000.;

   render->triangles_nb = 4;
   render->spheres_nb = 1;
   render->planes_nb = 1;
   render->lights_nb = 2;
   render->cones_nb = 1;
   render->circles_nb = 1;
   render->cylinders_nb = 1;

   render->rays = (t_ray *)malloc(sizeof(t_ray) * render->w_width * render->w_height);
   render->triangles = (t_triangle *)malloc(sizeof(t_triangle) * render->triangles_nb);
   render->spheres = (t_sphere *)malloc(sizeof(t_sphere) * render->spheres_nb);
   render->planes = (t_triangle *)malloc(sizeof(t_triangle) * render->planes_nb);
   render->cylinders = (t_cylinder *)malloc(sizeof(t_cylinder) * render->cylinders_nb);
   render->cones = (t_cone *)malloc(sizeof(t_cone) * render->cones_nb);
   render->circles = (t_circle *)malloc(sizeof(t_circle) * render->circles_nb);
   render->lights = (t_light *)malloc(sizeof(t_light) * render->lights_nb);
   render->textures = (t_texture *)malloc(sizeof(t_texture) * 1);

   render->triangles[0].a = (t_vector){0, -20, 60, 1};
   render->triangles[0].b = (t_vector){0, -10, 100, 1};
   render->triangles[0].c = (t_vector){40, -10, 60, 1};
   render->triangles[0].specular = 25;
   render->triangles[1].a = (t_vector){40, 0, 100, 1};
   render->triangles[1].b = render->triangles[0].b;
   render->triangles[1].c = render->triangles[0].c;
   render->triangles[1].specular = 25;
   render->triangles[2].a = (t_vector){20, 30, 80, 1};
   render->triangles[2].b = (t_vector){20, 40, 120, 1};
   render->triangles[2].c = (t_vector){60, 40, 80, 1};
   render->triangles[2].specular = 25;
   render->triangles[3].a = (t_vector){60, 50, 120, 1};
   render->triangles[3].b = render->triangles[2].b;
   render->triangles[3].c = render->triangles[2].c;
   render->triangles[3].specular = 25;

   render->planes[0].a = (t_vector){0, 20, -30, 1};
   render->planes[0].b = (t_vector){20, 20, -30, 1};
   render->planes[0].c = (t_vector){20, 0, -30, 1};
   render->planes[0].specular = 50;

   render->circles[0].plane.a = (t_vector){-10, 30, 30, 1};
   render->circles[0].plane.b = (t_vector){-10, 50, 50, 1};
   render->circles[0].plane.c = (t_vector){20, 30, 30, 1};
   render->circles[0].r = 20;
   render->circles[0].specular = 5;

   render->cylinders[0].center = (t_vector){-100, 20, 40, 1};
   render->cylinders[0].h_vec = vector_normalize((t_vector){0, 0, -1, 0});
   render->cylinders[0].r = 20;
   render->cylinders[0].r_vec = vector_normalize((t_vector){1, 0, 0, 0});
   render->cylinders[0].r_vec = vector_matrix_multiply(render->cylinders[0].r_vec, z_rotation_matrix(180. * M_PI / 180));
   render->cylinders[0].specular = 50;
   render->cylinders[0].h = 40;

   render->spheres[0].center = (t_vector){50, 80, 10, 1};
   render->spheres[0].r = 30;
   render->spheres[0].latitude = vector_normalize((t_vector){0, 0, 1, 0});
   render->spheres[0].longitude = vector_normalize((t_vector){1, 0, 0, 0});
   render->spheres[0].specular = 50;

   render->cones[0].tip = (t_vector){-50, 20, 40, 1};
   render->cones[0].direction = vector_normalize((t_vector){0, 0, -1, 0});
   render->cones[0].angle = 30. * M_PI / 180;
render->cones[0].r_vec = vector_normalize((t_vector){1, 0, 0, 1});
render->cones[0].r_vec = vector_matrix_multiply(render->cones[0].r_vec, z_rotation_matrix(90. * M_PI / 180));
render->cones[0].h = 40;
render->cones[0].specular = 50;

render->lights[0].position = (t_vector){-100, -70, 80, 1};
render->lights[0].intensity = 1;
//	render->lights[1].position = (t_vector){50, 80, 150, 1};
//	render->lights[1].intensity = 0.4;
render->lights[1].position = (t_vector){90, -50, 120, 1};
render->lights[1].intensity = 0.8;
render->textures[0].color = 0xffff00;
}
*/
