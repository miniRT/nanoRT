/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:15:08 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/16 18:50:46 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "structures.h"
# include "utils.h"

void        init_camera(t_camera *cam);

t_object    *object(t_object_type type, void *element, t_color3 albedo);
t_light     *light_point(t_point3 light_origin, t_color3 light_color, double bright_ratio);
t_sphere    *sphere(t_point3 center, double radius);
t_plane     *plane(t_point3 center, t_vec3 dir);
t_cylinder  *cylinder(t_point3 center, t_vec3 dir, float diameter, float height);
#endif