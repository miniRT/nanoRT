#include "trace.h"

void print_vec(t_vec3 vec3)
{
    printf ("x : %f, y :%f, z : %f\n", vec3.x, vec3.y, vec3.z);
}

//ray 생성자(정규화 된 ray)
t_ray       ray(t_point3 orig, t_vec3 dir)
{
    t_ray ray;

    ray.orig = orig;
    ray.dir = vunit(dir);
    return (ray);
}

//ray origin point 부터 방향벡터 ray dir * t 만큼 떨어진 점.
t_point3    ray_at(t_ray *ray, double t)
{
    t_point3 at;

    at = vplus(ray->orig, vmult(ray->dir, t));
    return (at);
}

//primary_ray 생성자
t_ray       ray_primary(t_camera *cam, double u, double v)
{
    t_ray   ray;

    ray.orig = cam->orig; // 0, 0, 0
    // left_bottom + (u * horizontal) + (v * vertical) - origin 의 단위 벡터.
    ray.dir = vunit(vminus(vplus(vplus(cam->left_bottom, vmult(cam->horizontal, u)), vmult(cam->vertical, v)), cam->orig));
    // print_vec(ray.dir); // 해당 뷰포트의 단위 백터, 가리키는 방향
    return (ray);
}

//광선이 최종적으로 얻게된 픽셀의 색상 값을 리턴.
t_color3    ray_color(t_ray *ray, t_sphere *sphere)
{
     double  t;

    if (hit_sphere(sphere, ray))
        return (color3(1, 1, 0));
    else
    {
        //ray의 방향벡터의 y 값을 기준으로 그라데이션을 주기 위한 계수.
        t = 0.5 * (ray->dir.y + 1.0);
        // (1-t) * 흰색 + t * 하늘색
            return (color3(0.5, 0.5, 0.5));
    }
}