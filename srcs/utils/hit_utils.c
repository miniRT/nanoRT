/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:40:31 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/17 11:40:52 by kimtaeseon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"

double	cy_boundary(t_cylinder *cy, t_vec3 at_point)
{
	double	hit_height;
	double	max_height;

	hit_height = vdot(vminus(at_point, cy->center), cy->dir);
	max_height = cy->height / 2;
	if (fabs(hit_height) > max_height)
		return (0);
	return (hit_height);
}

t_vec3	get_cylinder_normal(t_cylinder *cy, t_vec3 at_point, double hit_height)
{
	t_point3	hit_center;
	t_vec3		normal;

	hit_center = vplus(cy->center, vmult(cy->dir, hit_height));
	normal = vminus(at_point, hit_center);
	return (vunit(normal));
}
