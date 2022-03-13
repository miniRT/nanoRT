#ifndef SCENE_H
# define SCENE_H

# include "structures.h"
# include "utils.h"

t_camera    camera(void);

t_object    *object(t_object_type type, void *element, t_color3 albedo);
t_light     *light_point(t_point3 light_origin, t_color3 light_color, double bright_ratio);
t_sphere    *sphere(t_point3 center, double radius);
t_plane     *plane(t_point3 center, t_vec3 normal);
t_cylinder  *cylinder(t_point3 center, t_vec3 normal, float diameter, float height);
#endif