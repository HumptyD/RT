/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:12:28 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/03/02 18:52:52 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		read_format(int fd)
{
	char	buf[2];

	read(fd, buf, 2);
	if (buf[0] == 'P')
		return (buf[1] - '0');
	else
		return (0);
}

int		read_size(t_picture *pic, int fd)
{
	char	buf;

	read(fd, &buf, 1);
	while (read(fd, &buf, 1))
	{
		if (ft_isdigit(buf) && pic->width == 0)
			while (ft_isdigit(buf))
			{
				pic->width = pic->width * 10 + buf - '0';
				read(fd, &buf, 1);
			}
		if (ft_isdigit(buf) && pic->height == 0)
			while (ft_isdigit(buf))
			{
				pic->height = pic->height * 10 + buf - '0';
				read(fd, &buf, 1);
			}
		if (buf == '\n')
			break ;
	}
	if (pic->width && pic->height)
		return (1);
	return (0);
}

int		read_max_value(int fd)
{
	char	buf;
	int		value;

	value = 0;
	while (read(fd, &buf, 1))
	{
		if (ft_isdigit(buf) && value == 0)
			while (ft_isdigit(buf))
			{
				value = value * 10 + buf - '0';
				read(fd, &buf, 1);
			}
		if (buf == '\n')
			break ;
	}
	if (value == 255)
		return (1);
	return (0);
}

int		read_picture(t_picture *pic, int fd)
{
	unsigned char	buf[3];
	int				i;
	
	if (!(pic->picture = (int *)malloc(sizeof(int) * pic->width * pic->height)))
		return (0);
	i = -1;
	while (++i < pic->width * pic->height && read(fd, buf, 3))
		pic->picture[i] = ((int)buf[0] << 16 | (int)buf[1] << 8 | (int)buf[2]);
	return (1);	
}

int		texture_reader(char *file, t_picture *pic)
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
	if (!read_picture(pic, fd))
		return (1);
	close(fd);
	return (0);
}


