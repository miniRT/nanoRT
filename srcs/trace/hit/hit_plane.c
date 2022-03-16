#include "structures.h"
#include "utils.h"
#include "trace.h"

static void print_vec(t_vec3 vec3)
{
    printf ("x : %f, y : %f, z : %f\n", vec3.x, vec3.y, vec3.z);
}

t_bool      hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec)
{
    t_plane *pl = pl_obj->element;
    float numrator; // 판별식의 분자
    float denominator; // 판별식의 분모
    float root;
    denominator = vdot(ray->dir, pl->dir);
    // print_vec( pl->dir);
    // print_vec(ray->dir);
    // printf ("denominator : %f\n", denominator);
    if (fabs(denominator) < EPSILON)
        return (FALSE);
    numrator = vdot(vminus(pl->center, ray->origin), pl->dir);
    // printf ("denominator : %f\n", denominator);
    // printf ("numrator : %f\n", numrator);
    root = numrator / denominator;
   
    if (root < rec->tmin || rec->tmax < root)
        return (FALSE);
    rec->t = root;
    rec->p = ray_at(ray, root);    
    rec->normal = pl->dir;
    set_face_normal(ray, rec);
    rec->albedo = pl_obj->albedo;
    printf ("cam dir ");
    print_vec(ray->dir);
    printf ("root : %f\n", root);
    printf ("hit point ");
    print_vec(rec->p);
    // print_vec(rec->albedo);
    return (TRUE);
}