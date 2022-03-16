#include "trace.h"

// static void print_vec(t_vec3 vec3)
// {
//     printf ("x : %f, y : %f, z : %f\n", vec3.x, vec3.y, vec3.z);
// }

t_bool      in_shadow(t_object *objs, t_ray light_ray, double light_len)
{
    t_hit_record rec;

    rec.tmin = EPSILON;
    rec.tmax = light_len; // light_len보다 길면 광원 뒤의 물체를 감지해 그림자가 생길 수 있다.
    if (hit(objs, &light_ray, &rec))
        return (TRUE);
    return (FALSE);
}

t_vec3      reflect(t_vec3 v, t_vec3 n) // 반사광 벡터 구하기
{
    double  ray_light_dot; // 교점에서 카메라로 향하는 벡터 v와 교점의 법선 벡터 N를 내적한 스칼라 값
    t_vec3  dot_vec;
    t_vec3  reverse_v; // 벡터 V를 반대방향으로 돌린 것, 역벡터
    
    ray_light_dot = vdot(v, n); // 벡터 V와 벡터 N를 내적한 값.
    dot_vec = vmult(n, ray_light_dot * 2);  // 내적한 값을 벡터화 시킨것 (벡터 N이 단위 벡터이기에 가능)
                                            // 2를 곱해주는 이유는 벡터 V를 역벡터화시켰기 때문.
    reverse_v = vmult(v, -1);    
    return (vplus(reverse_v, dot_vec));
}

t_color3    point_light_get(t_scene *scene, t_light *light)
{
    t_color3    diffuse; 

    t_vec3      light_dir; // 빛의 방향 벡터
    double      kd; // 난반사의 강도

    double  light_len;
    t_ray   light_ray;

    light_dir = vminus(light->origin, scene->rec.p); // 교점에서 출발하여 광원을 향하는 벡터, 해당 광선까지의 거리를 구해야 하기 때문에 표준화는 잠시 미뤄둔다.
    light_len = vlength(light_dir);
    light_ray = ray(vplus(scene->rec.p, vmult(scene->rec.normal, EPSILON)), light_dir);
    // 새로운 광선의 원점으로 rec->p인 충돌한 지점(교점), 방향 벡터로 충돌점에서 광선으로 향하는 벡터가 된다.

    // if (in_shadow(scene->world, light_ray, light_len))
    //     return (color3(0,0,0));

    light_dir = vunit(light_dir); //교점에서 출발하여 광원을 향하는 벡터(정규화)
    kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);// (교점에서 출발하여 광원을 향하는 벡터)와 (교점에서의 법선벡터)의 내적값.
    // 단위 백터 끼리의 내적이므로 교점의 법선 벡터와 광선으로 향하는 벡터의 내적값 cosΘ는 사이각이 된다.
    // cosΘ는 Θ 값이 90도 일 때 0이고 Θ가 둔각이 되면 음수가 되므로 0.0보다 작은 경우는 0.0으로 대체한다.
    // fmax 함수는 두 개의 인자 중 큰 값을 리턴한다. 만약 코사인세타가 둔각이 될 경우 음수가 되기에 0을 리턴하도록 한다.
    diffuse = vdivide(light->light_color, 255);
        // print_vec(diffuse);
    diffuse = vmult(diffuse, light->bright_ratio);
    diffuse = vmult(diffuse, kd);
    diffuse = vmult_(diffuse, scene->rec.albedo);

    return (diffuse);
}   

t_color3    phong_lighting(t_scene *scene)
{
    t_color3    rec_color;
    t_color3    light_color;
    t_color3    ambient_color;
    t_object    *lights;

    rec_color = scene->rec.albedo;
    light_color = color3(0, 0, 0);
    lights = scene->light;
    while (lights) // 존재하는 모든 광원들에 대한 정반사, 난반사 값을 연결리스트로 돌아가면서 구해준다.
    {
        if (lights->type == LIGHT_POINT)
            light_color = vplus(light_color, point_light_get(scene, lights->element));
            lights = lights->next;

    }
    // ambient_color = vmult(vmult_(scene->rec.albedo, scene->ambient.light_color), scene->ambient.bright_ratio);
   
    ambient_color = vdivide(scene->ambient.light_color, 255);
    ambient_color = vmult(ambient_color, scene->ambient.bright_ratio);
    ambient_color = vmult_(ambient_color, rec_color);
    
    // print_vec(ambient_color);
    // print_vec(light_color);

    // light_color = add_light(light_color, )
    // light_color = vplus(light_color, vmult(scene->ambient.light_color, scene->ambient.bright_ratio));
    //    print_vec(light_color);
   // 정반사, 난반사 값을 더했다면 주변광(기본적으로 들어가는 빛, scene->ambient)을 더해준다.
        return (vmin(vplus(light_color, ambient_color), color3(255.999999, 255.999999, 255.99999)));
    // 모든 광원에 의한 빛의 양을 구한 후, 충돌한  오브젝트의  색깔을 곱한다. 그 값이 (1, 1, 1)을 넘으면 (1, 1, 1)을 반환한다.
}