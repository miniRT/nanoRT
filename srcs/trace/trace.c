/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:55:36 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/01 17:35:16 by kimtaeseon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/trace.h"

t_ray	ray(t_point3 orig, t_vec3 dir)
{
	t_ray	ray;

	ray.origin = orig;
	ray.dir = vunit(dir);
	return (ray);
}

t_point3	ray_at(t_ray *ray, double t)
{
	t_point3	at;

	at = vplus(ray->origin, vmult(ray->dir, t));
	return (at);
}

t_ray	ray_primary(t_camera *cam, double u, double v)
{
	t_ray	ray;

	ray.origin = cam->orig;
	ray.dir = vunit(vminus(vplus(vplus(cam->left_bottom,
						vmult(cam->horizontal, u)),
					vmult(cam->vertical, v)), cam->orig));
	return (ray);
}

t_color3	ray_color(t_ray *r)
{
	double	t;

	t = 0.5 * (r->dir.y + 1.0);
	return (vplus(vmult(color3(1, 1, 1), 1.0 - t),
			vmult(color3(0.5, 0.7, 1.0), t)));
}
