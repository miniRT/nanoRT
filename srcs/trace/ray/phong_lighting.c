/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 22:49:01 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/18 12:18:57 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

t_bool	in_shadow(t_object *objs, t_ray light_ray, double light_len)
{
	t_hit_record	rec;

	rec.tmin = EPSILON;
	rec.tmax = light_len;
	if (hit(objs, &light_ray, &rec))
		return (TRUE);
	return (FALSE);
}

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	double	ray_light_dot;
	t_vec3	dot_vec;
	t_vec3	reverse_v;

	ray_light_dot = vdot(v, n);
	dot_vec = vmult(n, ray_light_dot * 2);
	reverse_v = vmult(v, -1);
	return (vplus(reverse_v, dot_vec));
}

t_color3	point_light_get(t_scene *scene, t_light *light)
{
	t_color3	diffuse;
	t_vec3		light_dir;
	double		kd;
	double		light_len;
	t_ray		light_ray;

	light_dir = vminus(light->origin, scene->rec.p);
	light_len = vlength(light_dir);
	light_ray = ray(vplus(scene->rec.p,
				vmult(scene->rec.normal, EPSILON)), light_dir);
	if (in_shadow(scene->world, light_ray, light_len))
		return (color3(0, 0, 0));
	light_dir = vunit(light_dir);
	kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);
	diffuse = vdivide(light->light_color, 255);
	diffuse = vmult(diffuse, light->bright_ratio);
	diffuse = vmult(diffuse, kd);
	diffuse = vmult_(diffuse, scene->rec.albedo);
	return (diffuse);
}

t_color3	phong_lighting(t_scene *scene)
{
	t_color3	rec_color;
	t_color3	light_color;
	t_color3	ambient_color;
	t_object	*lights;

	rec_color = scene->rec.albedo;
	light_color = color3(0, 0, 0);
	lights = scene->light;
	while (lights)
	{
		if (lights->type == LIGHT_POINT)
			light_color = vplus(light_color, \
			point_light_get(scene, lights->element));
		lights = lights->next;
	}
	ambient_color = vdivide(scene->ambient.light_color, 255);
	ambient_color = vmult(ambient_color, scene->ambient.bright_ratio);
	ambient_color = vmult_(ambient_color, rec_color);
	return (vmin(vplus(light_color, ambient_color),
			color3(255, 255, 255)));
}
