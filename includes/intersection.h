/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 17:06:51 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/02/21 17:13:19 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "rtv1.h"
# include "vector.h"

typedef struct	s_cone_inter
{
	t_vector	co;
	double		t0;
	double		t1;
	double		dv;
	double		cov;
	double		cos_a;
}				t_cone_inter;

#endif
