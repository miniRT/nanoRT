/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:50:05 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/17 17:57:23 by kimtaeseon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "structures.h"

void		ft_exit(int code);
t_vec3		vec3(double x, double y, double z);
t_point3	point3(double x, double y, double z);
t_point3	color3(double r, double g, double b);
void		vset(t_vec3 *vec, double x, double y, double z);
double		vlength2(t_vec3 vec);
double		vlength(t_vec3 vec);
t_vec3		vplus(t_vec3 vec, t_vec3 vec2);
t_vec3		vplus_(t_vec3 vec, double x, double y, double z);
t_vec3		vminus(t_vec3 vec, t_vec3 vec2);
t_vec3		vminus_(t_vec3 vec, double x, double y, double z);
t_vec3		vmult(t_vec3 vec, double t);
t_vec3		vmult_(t_vec3 vec, t_vec3 vec2);
t_vec3		vdivide(t_vec3 vec, double t);
double		vdot(t_vec3 vec, t_vec3 vec2);
t_vec3		vcross(t_vec3 vec, t_vec3 vec2);
t_vec3		vunit(t_vec3 vec);
t_vec3		vmin(t_vec3 vec1, t_vec3 vec2);
void		oadd(t_object **list, t_object *new);
t_object	*olast(t_object *list);
double		cy_boundary(t_cylinder *cy, t_vec3 at_point);
t_vec3		get_cylinder_normal(t_cylinder *cy,
				t_vec3 at_point, double hit_height);

#endif
