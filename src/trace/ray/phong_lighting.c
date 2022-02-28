#include "trace.h"


t_vec3      reflect(t_vec3 v, t_vec3 n) // 반사광 벡터 구하기
{
    double vec_dot;
    
    vec_dot = vdot(v, n) * 2; // v과 n의 내적 * 2
    // v - (2 * dot(v, n) * n);
    return (vminus(v, vmult(n, vec_dot)));
}

t_color3    point_light_get(t_scene *scene, t_light *light)
{
    t_color3    diffuse; 
    t_vec3      light_dir; // 빛의 방향 벡터
    double      kd; // 난반사의 강도

    t_color3    specular; 
    t_vec3       view_dir; // 카메라 원점을 향하는 벡터 
    t_vec3       reflect_dir; // 법전을 기준으로 광선의 벡터를 대칭시킨 벡터
    double      spec; // 사이각의 크기에 따른 코사인 값
    double      ksn; // 반짝거리는 정도
    double      ks; // 

    light_dir = vunit(vminus(light->origin, scene->rec.p)); //교점에서 출발하여 광원을 향하는 벡터(정규화)
    // rec.p는 해당 광선(레이)가 뻗어나가면서 가장 먼저 마주친 물체의 교점에 대한 값이다.
    // cosΘ는 Θ 값이 90도 일 때 0이고 Θ가 둔각이 되면 음수가 되므로 0.0보다 작은 경우는 0.0으로 대체한다.
    kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);// (교점에서 출발하여 광원을 향하는 벡터)와 (교점에서의 법선벡터)의 내적값.
    // fmax 함수는 두 개의 인자 중 큰 값을 리턴한다. 만약 코사인세타가 둔각이 될 경우 음수가 되기에 0을 리턴하도록 한다.
    diffuse = vmult(light->light_color, kd);

    printf ("\n 광원을 향하는 벡터와 법선 벡터의 내적 값 : %f 난반사의 강도 %f \n",vdot(scene->rec.normal, light_dir),  kd);

    view_dir = vunit(vmult(scene->ray.dir, -1));
    reflect_dir = reflect(vmult(light_dir, -1), scene->rec.normal);
    ksn = 64;
    ks = 0.5;
    spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
    specular = vmult(vmult(light->light_color, ks), spec);
    
    return (vplus(diffuse, specular));
}   


t_color3    phong_lighting(t_scene *scene)
{
    t_color3    light_color;
    t_object    *lights;

    light_color = color3(0, 0, 0);
    lights = scene->light;
    while (lights) // 존재하는 모든 광원들에 대한 정반사, 난반사 값을 연결리스트로 돌아가면서 구해준다.
    {
        if (lights->type == LIGHT_POINT)
            light_color = vplus(light_color, point_light_get(scene, lights->element));
            lights = lights->next;
    }
    // 정반사, 난반사 값을 더했다면 주변광(기본적으로 들어가는 빛, scene->ambient)을 더해준다.
    light_color = vplus(light_color, scene->ambient);
        return (vmin(vmult_(light_color, scene->rec.albedo), color3(1, 1, 1)));
    // 이걸 왜 해주는데?
    // 모든 광원에 의한 빛의 양을 구한 후, 오브젝트의 반사율과 곱해준다. 그 값이 (1, 1, 1)을 넘으면 (1, 1, 1)을 반환한다.

}