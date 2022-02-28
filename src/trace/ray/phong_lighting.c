#include "trace.h"

t_color3    point_light_get(t_scene *scene, t_light *light)
{
    t_color3    diffuse; 
    t_vec3      light_dir; // 빛의 방향 벡터
    double      kd; // 난반사의 강도
    
    light_dir = vunit(vminus(light->origin, scene->rec.p)); //교점에서 출발하여 광원을 향하는 벡터(정규화)
    // cosΘ는 Θ 값이 90도 일 때 0이고 Θ가 둔각이 되면 음수가 되므로 0.0보다 작은 경우는 0.0으로 대체한다.
    kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);// (교점에서 출발하여 광원을 향하는 벡터)와 (교점에서의 법선벡터)의 내적값.
    // fmax 함수는 두 개의 인자 중 큰 값을 리턴한다. 만약 코사인세타가 둔각이 될 경우 음수가 되기에 0을 리턴하도록 한다.
    diffuse = vmult(light->light_color, kd);
    return (diffuse);
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
    // 정반사, 난반사 값을 더했다면 주변광을 더해준다.
    light_color = vplus(light_color, scene->ambient);
        return (vmin(vmult_(light_color, scene->rec.albedo), color3(1, 1, 1)));
    // 이걸 왜 해주는데?
    // 모든 광원에 의한 빛의 양을 구한 후, 오브젝트의 반사율과 곱해준다. 그 값이 (1, 1, 1)을 넘으면 (1, 1, 1)을 반환한다.

}