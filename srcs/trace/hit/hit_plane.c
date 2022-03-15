#include "structures.h"
#include "utils.h"
#include "trace.h"

t_bool      hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec)
{
    t_plane *pl = pl_obj->element;
    float numrator; // 판별식의 분자
    float denominator; // 판별식의 분모
    float root;
    denominator = vdot(ray->dir, pl->dir);
    if (denominator < EPSILON)
        return (FALSE);
    numrator = vdot(vminus(pl->center, ray->origin), pl->dir);
    // printf ("denominator : %f\n", denominator);
    // printf ("numrator : %f\n", numrator);
    root = numrator / denominator;
    // printf ("root : %f\n", root);
    if (root < rec->tmin || rec->tmax < root)
        return (FALSE);
    rec->t = root;
    rec->p = ray_at(ray, root);    
    rec->normal = pl->dir;
    set_face_normal(ray, rec);
    rec->albedo = pl_obj->albedo;
    return (TRUE);
}