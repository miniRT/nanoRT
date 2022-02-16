#include "structures.h"
#include "utils.h"
#include "trace.h"

static void print_vec(t_vec3 vec3)
{
    printf ("x : %f, y : %f, z : %f\n", vec3.x, vec3.y, vec3.z);
}

t_bool      hit_sphere(t_sphere *sp, t_ray *ray, t_hit_record *rec)
{
    t_vec3  oc; // 0에서부터 벡터로 나타낸 구의 중심. 
    //a, b, c는 각각 t에 관한 근의 공식 2차 방정식의 계수
    double  a;
	double  half_b;    // b가 half_b로
    double  c;
    double  discriminant; // 판별식

    double sqrtd;
    double root;

    t_vec3 half;

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
    if (root < rec->tmin || rec->tmax < root)
    {
        root = (-half_b + sqrtd) / a; // 큰 근 역시 tmin, tmax와의 비교
        if (root < rec->tmin || rec->tmax < root) //  큰 근조차 tmin보다 작다면 hit하지 않은 것이므로 FALSE를 반환.
        return (FALSE);
    }
    rec->t = root; // 광선의 원점과 교점까지의 거리
    rec->p = ray_at(ray, root); // 교점의 좌표

    printf ("t : %f\n", rec->t);
    printf ("좌표 : ");
    print_vec(rec->p);

    half = vminus(rec->p, sp->center);
    printf ("반지름 -> 교점 벡터 : ");
    print_vec(half);
    rec->normal = vdivide(half, sp->radius);
    printf ("단위 벡터인 법선 : ");
    print_vec(rec->normal);
    // 해당 교점으로부터 뻗어나오는 정규화된 법선벡터를 구하는 함수.
    // 원의 중심에서부터 교점(테두리)를 향하는 벡터를 반지름으로 나누면 곧 표준백터가 된다.
    set_face_normal(ray, rec); // 카메라가 구의 안쪽에 있을 경우 광선과 법선은 같은 방향을 향하게 된다. 법선과 광선이 반대방향을 향햐도록 확인하는 함수를 추가했다.
    return (TRUE);
}