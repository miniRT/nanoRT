#include "trace.h"

static void print_vec(t_vec3 vec3)
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

    t_vec3  horizontal;
    t_vec3  vertical;
    t_vec3  unitvect;

    ray.orig = cam->orig; // 0, 0, 0
    // left_bottom + (u * horizontal) + (v * vertical) - origin 의 단위 벡터.
    horizontal = vmult(cam->horizontal, u);
    vertical = vmult(cam->vertical, v);
    
    unitvect = cam->left_bottom;
    unitvect = vplus(unitvect, horizontal);
    unitvect = vplus(unitvect, vertical);               

    unitvect = vminus(unitvect, cam->orig); // 0, 0, 0. 의미가 없는데? 카메라가 변경될 때를 고려한 건가?
                // printf ("minus : "); // 이 시점에서 가로와 세로의 벡터 합 계산이 완료되었다.
                // print_vec(unitvect); 
    unitvect = vunit(unitvect);
                printf ("단위 백터 : ");
                print_vec(unitvect); // 해당 뷰포트의 단위 백터, 가리키는 방향
    ray.dir = unitvect;

    // ray.dir = vunit(vminus(vplus(vplus(cam->left_bottom,vmult(cam->horizontal, u)), vmult(cam->vertical, v)), cam->orig));
    return (ray);
}

//광선이 최종적으로 얻게된 픽셀의 색상 값을 리턴.
t_color3    ray_color(t_ray *ray, t_sphere *sphere)
{
    double  t;
    t_vec3  n;

    t = hit_sphere(sphere, ray);
    if (t > 0.0)
    {
        //정규화 된 구 표면에서의 법선
        n = vunit(vminus(ray_at(ray, t), sphere->center));
        return (vmult(color3(n.x + 1, n.y + 1, n.z + 1), 0.5));
    }
    else
    {
        // (1-t) * 흰색 + t * 하늘색
            return (color3(0.5, 0.5, 0.5));
    }
}