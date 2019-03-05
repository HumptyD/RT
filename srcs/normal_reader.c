/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:38:02 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/02 18:53:07 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		read_normal(t_picture *pic, int fd)
{
	unsigned char	buf[3];
	int i;

	if (!(pic->normals = (t_vector *)malloc(sizeof(t_vector) * pic->width * pic->height)))
		return (0);
	i = -1;
	while (++i < pic->width * pic->height && read(fd, buf, 3))
	{
		pic->normals[i].x = buf[0] - 128;
		pic->normals[i].y = buf[1] - 128;
		pic->normals[i].z = buf[2] - 128;
		pic->normals[i].w = 0.;
		pic->normals[i] = vector_normalize(pic->normals[i]);
	}
	return (1);
}

int		normal_reader(char *file, t_picture *pic)
{
	int	fd;

	pic->width = 0;
	pic->height = 0;
	if (!(fd = open(file, O_RDONLY)))
		return (1);
	if (!read_format(fd))
		return (1);
	if (!read_size(pic, fd))
		return (1);
	if (!read_max_value(fd))
		return (1);
	if (!read_normal(pic, fd))
		return (1);
	close(fd);
	return (0);
}
