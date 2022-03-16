/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 22:49:12 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/16 22:49:44 by kimtaeseon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/trace.h"

t_ray	ray(t_point3 origin, t_vec3 dir)
{
	t_ray	ray;

	ray.origin = origin;
	ray.dir = vunit(dir);
	return (ray);
}

t_point3	ray_at(t_ray *ray, double t)
{
	t_point3	at;

	at = vplus(ray->origin, vmult(ray->dir, t));
	return (at);
}

t_ray	ray_primary(t_camera *cam, int x, int y)
{
	t_ray	ray;
	t_vec3	horizontal;
	t_vec3	vertical;
	t_vec3	ray_vec;

	ray.origin = cam->origin;
	horizontal = vmult(cam->right_normal, (double)x);
	vertical = vmult(cam->up_normal, (double)y);
	ray_vec = cam->left_bottom;
	ray_vec = vplus(ray_vec, horizontal);
	ray_vec = vplus(ray_vec, vertical);
	ray_vec = vminus(ray_vec, cam->origin);
	ray_vec = vunit(ray_vec);
	ray.dir = ray_vec;
	if (x == 150 && y == 75)
		printf ("now!");
	return (ray);
}

t_hit_record	record_init(void)
{
	t_hit_record	record;

	record.tmin = EPSILON;
	record.tmax = 1000;
	return (record);
}

t_color3	ray_color(t_scene *scene)
{
	scene->rec = record_init();
	if (hit(scene->world, &scene->ray, &scene->rec))
		return (phong_lighting(scene));
	else
		return (color3(0, 0, 0));
}
