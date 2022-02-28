#include "trace.h"

t_color3    phong_lighting(t_scene *scene)
{
    t_color3    light_color;
    t_object    *lights;

    light_color = color3(0, 0, 0);
    lights = scene->light;
    // while (lights) // 존재하는 모든 광원들에 대한 정반사, 난반사 값을 연결리스트로 돌아가면서 구해준다.
    // {
    //     if (lights->type == LIGHT_POINT)
    //         light_color = vplus(light_color, point_light_get(scene, lights->element));
    //         lights = lights->next;
    // }
    // 정반사, 난반사 값을 더했다면 주변광을 더해준다.
    light_color = vplus(light_color, scene->ambient);
        return (vmin(vmult_(light_color, scene->rec.albedo), color3(1, 1, 1)));
    // 이걸 왜 해주는데?
    // 모든 광원에 의한 빛의 양을 구한 후, 오브젝트의 반사율과 곱해준다. 그 값이 (1, 1, 1)을 넘으면 (1, 1, 1)을 반환한다.

}