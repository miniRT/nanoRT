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
    
    oc = vminus(ray->origin, sp->center); // 0, 0, 0 - 구의 중심점
    a = vlength2(ray->dir);
    half_b = vdot(oc, ray->dir);
    c = vlength2(oc) - sp->radius2;
    discriminant = half_b * half_b - a * c;

    if (discriminant < 0) 
        return (FALSE);
    sqrtd = sqrt(discriminant); // 판별식에 루트를 씌움.
    root = (-half_b - sqrtd) / a; // 근의 공식 해, 작은 근부터 고려.
    // 해당 광선과 교점까지의 거리 사이에 다른 물체가 있거나 너무 멀리 있는 경우를 체크
    if (root < rec->tmin || rec->tmax < root) // rec->tmax는 해당 광선으로부터 가장 가까운 물체를 의미
    {
        root = (-half_b + sqrtd) / a; // 큰 근 역시 tmin, tmax와의 비교
        if (root < rec->tmin || rec->tmax < root) //  큰 근조차 tmin보다 작다면 hit하지 않은 것이므로 FALSE를 반환.
        return (FALSE);
    }
    rec->t = root; // 광선의 원점과 교점까지의 거리를 rec에 저장한다.
    rec->p = ray_at(ray, root); // 교점의 좌표를 rec에 저장한다.
    normal = vminus(rec->p, sp->center); // 법선 벡터
    rec->normal = vdivide(normal, sp->radius);
    set_face_normal(ray, rec); // 카메라가 구의 안쪽에 있을 경우 광선과 법선은 같은 방향을 향하게 된다. 법선과 광선이 반대방향을 향햐도록 확인하는 함수를 추가했다.
    rec->albedo = sp_obj->albedo;
    return (TRUE);
}
