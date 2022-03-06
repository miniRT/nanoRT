#include "structures.h"
#include "utils.h"
#include "trace.h"

// static void print_vec(t_vec3 vec3)
// {
//     printf ("x : %f, y : %f, z : %f\n", vec3.x, vec3.y, vec3.z);
// }

t_bool      hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
    t_sphere *sp;
    t_vec3  oc; // 0에서부터 벡터로 나타낸 구의 중심. 
    t_vec3 normal; // 법선 벡터, 표준 벡터가 아니다!

    //a, b, c는 각각 t에 관한 근의 공식 2차 방정식의 계수
    double  a;
	double  half_b;    // b가 half_b로
    double  c;
    double  discriminant; // 판별식

    double sqrtd;
    double root;


    sp = sp_obj->element;
    
    oc = vminus(ray->orig, sp->center); // 0, 0, 0 - 구의 중심점
    // a = vdot(ray->dir, ray->dir); // 항상 1? 1로 딱 떨어지지 않는데?
    // 벡터의 내적, 그러나 동일한 벡터끼리의 내적이기에 벡터의 길이의 제곱과 같다
    // half_b = vdot(oc, ray->dir); // b = 2 * vdot(oc, ray->dir);
    //  c = vdot(oc, oc) - sp->radius2;
    //  discriminant = b * b - 4 * a * c;
    a = vlength2(ray->dir);
    half_b = vdot(oc, ray->dir);
    c = vlength2(oc) - sp->radius2;
    discriminant = half_b * half_b - a * c;

    // printf ("a : %f, b: %f, c : %f, 판별식 : %f", a, half_b, c, discriminant);

    if (discriminant < 0) 
        return (FALSE);
    // 이 시점에서 판별식이 참이 나왔기에 근이 존재한다고 판단한다.

    sqrtd = sqrt(discriminant); // 판별식에 루트를 씌움.
    root = (-half_b - sqrtd) / a; // 근의 공식 해, 작은 근부터 고려.
    // 해당 광선과 교점까지의 거리 사이에 다른 물체가 있거나 너무 멀리 있는 경우를 체크
    if (root < rec->tmin || rec->tmax < root) // rec->tmax는 해당 광선으로부터 가장 가까운 물체를 의미
    {
        root = (-half_b + sqrtd) / a; // 큰 근 역시 tmin, tmax와의 비교
        if (root < rec->tmin || rec->tmax < root) //  큰 근조차 tmin보다 작다면 hit하지 않은 것이므로 FALSE를 반환.
        return (FALSE);
    }
    
    // 조건문을 통과 == 현재까지 해당 광선이 충돌한 물체 중 가장 가까운 물체임을 의미

    rec->t = root; // 광선의 원점과 교점까지의 거리를 rec에 저장한다.
    rec->p = ray_at(ray, root); // 교점의 좌표를 rec에 저장한다.
  
    normal = vminus(rec->p, sp->center); // 법선 벡터
    
    // printf ("원의 중심 - 교점 -> 법선 벡터 : ");
    // print_vec(normal);
    rec->normal = vdivide(normal, sp->radius);
    // 해당 교점의 법선 벡터를 정규화하는 함수.
    // 단위 백터를 구하려면 벡터의 각 요소를 벡터의 길이로 나누어주면 된다.
    // vunit을 써줄 필요까지 없이 반지름이 곧 벡터의 길이이자 스칼라이므로 반지름으로 나누면 표준벡터가 된다.
    // printf ("정규화된 법선 벡터 : ");
    // print_vec(rec->normal);
    // printf ("표준 벡터 : %f %f\n", vlength(rec->normal), vlength(ray->dir));

    set_face_normal(ray, rec); // 카메라가 구의 안쪽에 있을 경우 광선과 법선은 같은 방향을 향하게 된다. 법선과 광선이 반대방향을 향햐도록 확인하는 함수를 추가했다.
    
    rec->albedo = sp_obj->albedo;
    return (TRUE);
}
