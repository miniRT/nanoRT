/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 22:35:39 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/16 23:07:18 by kimtaeseon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "trace.h"

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

int	hit_cylinder_cap(t_object *cy_obj, t_ray *ray,
	t_hit_record *rec, double height)
{
	t_cylinder	*cy;
	double		r;
	t_vec3		circle_center;
	float		root ;
	float		diameter ;

	cy = cy_obj->element;
	r = cy->diameter / 2;
	circle_center = vplus(cy->center, vmult(cy->dir, height));
	root = vdot(vminus(circle_center, ray->origin), cy->dir) \
		/ vdot(ray->dir, cy->dir);
	diameter = vlength(vminus(circle_center, ray_at(ray, root)));
	if (fabs(r) < fabs(diameter))
		return (0);
	if (root < rec->tmin || rec->tmax < root)
		return (0);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->tmax = rec->t;
	if (0 < height)
		rec->normal = cy->dir;
	else
		rec->normal = vmult(cy->dir, -1);
	set_face_normal(ray, rec);
	rec->albedo = cy_obj->albedo;
	return (1);
}

int	hit_cylinder_side(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	double		a;
	double		half_b;
	double		c;
	t_vec3		u;
	t_vec3		o;
	t_vec3		delta_P;
	double		r;
	double		discriminant;
	double		sqrtd;
	double		root;
	double		hit_height;

	cy = cy_obj->element;
	u = ray->dir;
	o = cy->dir;
	r = cy->diameter / 2;
	delta_P = vminus(ray->origin, cy->center);
	a = vlength2(vcross(u, o));
	half_b = vdot(vcross(u, o), vcross(delta_P, o));
	c = vlength2(vcross(delta_P, o)) - pow(r, 2);
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (0);
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
	root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (0);
	}
	hit_height = cy_boundary(cy, ray_at(ray, root));
	if (!(hit_height))
		return (0);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = get_cylinder_normal(cy, rec->p, hit_height);
	set_face_normal(ray, rec);
	rec->albedo = cy_obj->albedo;
	return (1);
}

t_bool	hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	const t_cylinder	*cy;
	int					result;

	cy = cy_obj->element;
	result = 0;
	result += hit_cylinder_cap(cy_obj, ray, rec, cy->height / 2);
	result += hit_cylinder_cap(cy_obj, ray, rec, -(cy->height / 2));
	result += hit_cylinder_side(cy_obj, ray, rec);
	return (result);
}
