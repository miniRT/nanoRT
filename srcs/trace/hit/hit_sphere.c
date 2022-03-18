/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 22:45:19 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/17 19:08:17 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "trace.h"

int	hit_sphere_value_setter(t_sphereops *sphere,
	t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
	sphere->sp = sp_obj->element;
	sphere->oc = vminus(ray->origin, sphere->sp->center);
	sphere->a = vlength2(ray->dir);
	sphere->half_b = vdot(sphere->oc, ray->dir);
	sphere->c = vlength2(sphere->oc) - sphere->sp->radius2;
	sphere->discriminant = sphere->half_b
		* sphere->half_b - sphere->a * sphere->c;
	if (sphere->discriminant < 0)
		return (FALSE);
	sphere->sqrtd = sqrt(sphere->discriminant);
	sphere->root = (-sphere->half_b - sphere->sqrtd) / sphere->a;
	if (sphere->root < rec->tmin || rec->tmax < sphere->root)
	{
		sphere->root = (-sphere->half_b + sphere->sqrtd) / sphere->a;
		if (sphere->root < rec->tmin || rec->tmax < sphere->root)
			return (FALSE);
	}
	rec->t = sphere->root;
	rec->p = ray_at(ray, sphere->root);
	return (TRUE);
}

t_bool	hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
	t_sphereops	sphere;

	sphere.sp = 0;
	if (!hit_sphere_value_setter(&sphere, sp_obj, ray, rec))
		return (FALSE);
	sphere.normal = vminus(rec->p, sphere.sp->center);
	rec->normal = vdivide(sphere.normal, sphere.sp->diameter);
	set_face_normal(ray, rec);
	rec->albedo = sp_obj->albedo;
	return (TRUE);
}
