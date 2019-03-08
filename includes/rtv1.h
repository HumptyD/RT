/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:11:39 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/08 17:23:52 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <SDL2/SDL.h>
# include <pthread.h>
# include <OpenCL/opencl.h>
# include "vector.h"
# include "libft.h"

# define THREAD_N 8

# define TRIANGLE 0
# define PLANE 1
# define CIRCLE 2
# define SPHERE 3
# define CYLINDER 4
# define CONE 5

# define AMBIENT 0
# define POINT 1
# define DIRECTED 2
# define PARALLEL 3

typedef struct	s_camera
{
	t_vector	position;
	double		vert;
	double		hor;
	double		focus;
	double		r;
}				t_camera;

typedef struct	s_ray
{
	t_vector 	origin;
	t_vector	direction;
}				t_ray;

typedef struct	s_sdl
{
	SDL_Window	*window;
	SDL_Event	event;
	SDL_Surface	*surface;
}				t_sdl;

typedef struct	s_picture
{
	int			*picture;
	t_vector	*normals;
	int			width;
	int			height;
}				t_picture;

typedef struct	s_texture
{
	t_picture	*picture;
	char		a;
	char		b;
}				t_texture;

typedef struct		s_light
{
	t_vector		position;
	t_vector		direction;
	double			angle;
	double			intensity;
	char			type;
}					t_light;

typedef	struct	s_quadric
{
	double		a;
	double		b;
	double		c;
}				t_quadric;

typedef struct	s_material
{
	double		albedo;
	double		specular;
	double		shininess;
	double		refraction;
	double		refractive_index;
	double		emittance;
	double		intensity;
}				t_material;

typedef struct	s_primitive
{
	const void	*primitive;
	char		type;
	t_material	*material;
	t_texture	*texture;
}				t_primitive;

typedef struct	s_intersection
{
	double		u;
	double		v;
	double		z;
	t_vector	point;
	t_vector	normal;
	t_primitive *primitive;
}				t_intersection;

typedef struct	s_object
{
	int			primitives_nb;
	t_primitive	*primitives;
}				t_object;

typedef struct	s_pixel
{
	t_vector	pixel;
	int			samples;
}				t_pixel;

typedef struct	s_render
{
	int			w_width;
	int			w_height;
	int			lights_nb;
	int			objects_nb;
	int			materials_nb;
	int			pictures_nb;
	int			textures_nb;
	int			trace_path;
	t_picture	*pictures;
	t_object	*objects;
	t_pixel		*pixels;
	t_sdl		sdl;
	t_camera	cam;
	t_ray		*rays;
	t_material	*materials;
	t_texture	*textures;
	t_light		*lights;
}				t_render;

void			keyboard(t_render *render, int *quit);
void			init(t_render *rendr);
void			ft_render(t_render *render);
void			ray_cast(t_render *render);
void			set_pixel(SDL_Surface *surface, int x, int y, unsigned int pixel);
void			normal_reverse(t_vector *normal, t_vector dir);
void			*get_unit_primitive(char type);
void			sphere_rotation(t_sphere *sphere, double x, double y, double z);
void			triangle_size(t_triangle *triangle, double ab, double ac);
void			triangle_translation(t_triangle *triangle, t_vector position);
void			triangle_rotation(t_triangle *triangle, double x, double y, double z);
void			cylinder_rotation(t_cylinder *cylinder, double x, double y, double z);
void			cone_rotation(t_cone *cone, double x, double y, double z);
void			compute_specular_albedo(t_vector *color, double *li, t_intersection inter);
void			compute_reflection_refraction(t_vector *color, t_material *mat);
void			init_color(t_vector *color);
void			mix_color(t_vector *color);
void			compute_lightning(t_render *render, t_intersection inter, t_ray ray, double *li);
void			get_pic_normal(t_intersection *inter);
void			clear_surface(SDL_Surface *surface);
void			init_pixels(t_render *render);
t_intersection	triangle_intersection(t_ray ray, t_triangle triangle);
t_intersection	sphere_intersection(t_ray ray, t_sphere sphere);
t_intersection	plane_intersection(t_ray ray, t_triangle plane);
t_intersection	cylinder_intersection(t_ray ray, t_cylinder cylinder);
t_intersection	cone_intersection(t_ray ray, t_cone cone);
t_intersection	circle_intersection(t_ray ray, t_circle	circle);
t_intersection	init_intersection(void);
t_intersection	get_closest_intersection(t_render *render, t_ray ray);
int				quadric_equation(t_quadric q, double *t0, double *t1);
int				is_shadow(t_render *render, t_ray l_ray, double l_ray_len);
int				normal_reader(char *file, t_picture *pic);
int				texture_reader(char *file, t_picture *pic);
int				read_format(int fd);
int				read_size(t_picture *pic, int fd);
int				read_max_value(int fd);
double			light_sphere_intersection(t_sphere sphere, t_ray light_ray);
double			light_triangle_intersection(t_triangle triangle, t_ray light_ray);
double			light_plane_intersection(t_triangle plane, t_ray light_ray);
double			light_cylinder_intersection(t_cylinder cylinder, t_ray ray);
double			light_cone_intersection(t_cone, t_ray ray);
double			light_circle_intersection(t_circle circle, t_ray ray);
t_vector		get_texture(t_intersection inter, t_texture texture);
t_vector		ray_tracing(t_render *render, t_ray ray, int reflection);
t_vector		path_tracing(t_render *render, t_ray ray, int depth);
t_sphere		init_sphere(void);
t_triangle		init_triangle(void);
t_circle		init_circle(void);
t_cylinder		init_cylinder(void);
t_cone			init_cone(void);
t_ray			reflected_ray(t_ray l_ray, t_intersection inter);
t_ray			refracted_ray(t_ray ray, t_intersection inter, double refr_index);
t_ray			random_ray(t_intersection inter);

#endif
