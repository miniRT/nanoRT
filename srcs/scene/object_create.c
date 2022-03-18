/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 22:31:00 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/18 13:08:43 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"

t_object	*object(t_object_type type, void *element, t_color3 color)
{
	t_object	*new;

	new = (t_object *)malloc(sizeof(t_object));
	if (!(new))
		return (NULL);
	new->type = type;
	new->element = element;
	new->next = NULL;
	new->color = color;
	return (new);
}

t_light	*light_point(t_point3 light_origin,
	t_color3 light_color, double bright_ratio)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	if (!(light))
		return (NULL);
	light->origin = light_origin;
	light->light_color = light_color;
	light->bright_ratio = bright_ratio;
	return (light);
}

t_sphere	*sphere(t_point3 center, double diameter)
{
	t_sphere	*sp;

	sp = (t_sphere *)malloc(sizeof(t_sphere));
	if (!(sp))
		return (NULL);
	sp->center = center;
	sp->diameter = diameter;
	sp->radius2 = (diameter / 2) * (diameter / 2);
	return (sp);
}

t_plane	*plane(t_point3 center, t_vec3 dir)
{
	t_plane	*pl;

	pl = (t_plane *)malloc(sizeof(t_plane));
	if (!(pl))
		return (NULL);
	pl->center = center;
	pl->dir = vunit(dir);
	return (pl);
}

t_cylinder	*cylinder(t_point3 center, t_vec3 dir, float diameter, float height)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!(cy))
		return (NULL);
	cy->center = center;
	cy->dir = vunit(dir);
	cy->diameter = diameter;
	cy->height = height;
	return (cy);
}
