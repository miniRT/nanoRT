#ifndef TRACE_H
# define TRACE_H

# include "structures.h"
# include "utils.h"

# define MAX 1000

t_ray       ray(t_point3 orig, t_vec3 dir);
t_ray       ray_primary(t_camera *cam, double u, double v);
t_point3    ray_at(t_ray *ray, double t);

t_color3    ray_color(t_scene *scene);

t_bool      hit(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool      hit_obj(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool      hit_sphere(t_object *world, t_ray *ray, t_hit_record *rec);
t_bool      hit_plane(t_object *world, t_ray *ray, t_hit_record *rec);

void        set_face_normal(t_ray *r, t_hit_record *rec);

#endif