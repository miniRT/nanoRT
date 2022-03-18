/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 22:35:39 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/18 12:39:03 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "trace.h"

int	hit_cylinder_cap(t_object *cy_obj, t_ray *ray,
	t_hit_record *rec, double height)
{
	t_cylinder	*cy;
	t_vec3		circle_center;
	double		r;
	float		root;

	cy = cy_obj->element;
	r = cy->diameter / 2;
	circle_center = vplus(cy->center, vmult(cy->dir, height));
	root = vdot(vminus(circle_center, ray->origin), cy->dir) \
		/ vdot(ray->dir, cy->dir);
	if (fabs(r) < fabs(vlength(vminus(circle_center, ray_at(ray, root)))))
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
	rec->color = cy_obj->color;
	return (1);
}

int	hit_cylinder_value_setter(t_cylinops *c,
	t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	c->cy = cy_obj->element;
	c->u = ray->dir;
	c->o = c->cy->dir;
	c->r = c->cy->diameter / 2;
	c->delta_p = vminus(ray->origin, c->cy->center);
	c->a = vlength2(vcross(c->u, c->o));
	c->half_b = vdot(vcross(c->u, c->o), vcross(c->delta_p, c->o));
	c->c = vlength2(vcross(c->delta_p, c->o)) - pow(c->r, 2);
	c->discriminant = c->half_b * c->half_b - c->a * c->c;
	if (c->discriminant < 0)
		return (0);
	c->sqrtd = sqrt(c->discriminant);
	c->root = (-c->half_b - c->sqrtd) / c->a;
	if (c->root < rec->tmin || rec->tmax < c->root)
	{
		c->root = (-c->half_b + c->sqrtd) / c->a;
		if (c->root < rec->tmin || rec->tmax < c->root)
			return (0);
	}
	c->hit_height = cy_boundary(c->cy, ray_at(ray, c->root));
	if (!(c->hit_height))
		return (0);
	return (1);
}

int	hit_cylinder_side(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinops	cylinder_ops;

	cylinder_ops.cy = 0;
	if (!hit_cylinder_value_setter(&cylinder_ops, cy_obj, ray, rec))
		return (0);
	rec->t = cylinder_ops.root;
	rec->p = ray_at(ray, cylinder_ops.root);
	rec->normal = get_cylinder_normal(cylinder_ops.cy,
			rec->p, cylinder_ops.hit_height);
	set_face_normal(ray, rec);
	rec->color = cy_obj->color;
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
