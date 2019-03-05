#include "rtv1.h"

t_cone	init_cone(void)
{
	t_cone cone;

	cone.tip = (t_vector){0, 0, 0, 1};
	cone.direction = (t_vector){0, 0, -1, 0};
	cone.r_vec = (t_vector){1, 0, 0, 0};
	cone.angle = 30. * M_PI / 180;
	cone.h = 30;
	return (cone);
}

void	cone_rotation(t_cone *cone, double x, double y, double z)
{
	t_matrix_4x4 m;

	m = matrix_multiply(x_rotation_matrix(x), y_rotation_matrix(y));
	m = matrix_multiply(m, z_rotation_matrix(z));
	cone->direction = vector_matrix_multiply(cone->direction, m);
	cone->r_vec = vector_matrix_multiply(cone->r_vec, m);
}
