#include "trace.h"
static void print_vec(t_vec3 vec3)
{
    printf ("x : %f, y : %f, z : %f\n", vec3.x, vec3.y, vec3.z);
}
t_bool hit(t_object *world, t_ray *ray, t_hit_record *rec)
{
    t_bool  hit_anything;
    t_hit_record *temp_rec;

    temp_rec = rec;
    hit_anything = FALSE;
    while (world) // world->next로 훑어가며 등록된 구조체를 전부 체크함
    {
        if (hit_obj(world, ray, temp_rec))
        {
            printf ("충돌 지점 ");
            print_vec(temp_rec->p);
            hit_anything = TRUE;
            temp_rec->tmax = temp_rec->t;
            rec = temp_rec;
        }
        world = world->next;
    }

    return (hit_anything);
}

t_bool hit_obj(t_object *world, t_ray *ray, t_hit_record *rec)
{
    t_bool hit_result;

    hit_result = FALSE;
    if (world->type == SP)
        hit_result = hit_sphere(world, ray, rec);
    else if (world->type == PL)
        hit_result = hit_plane(world, ray, rec);
    else if (world->type == CY)
        hit_result = hit_cylinder(world, ray, rec);
    return (hit_result);
}