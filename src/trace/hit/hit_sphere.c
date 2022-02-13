#include "structures.h"
#include "utils.h"



double      hit_sphere(t_sphere *sp, t_ray *ray)
{
    t_vec3  oc; // 0에서부터 벡터로 나타낸 구의 중심.
    //a, b, c는 각각 t에 관한 근의 공식 2차 방정식의 계수
    double  a;
	double  half_b;    // b가 half_b로
    double  c;
    double  discriminant; //판별식

    oc = vminus(ray->orig, sp->center);
    a = vdot(ray->dir, ray->dir);
    b = vdot(oc, ray->dir);
    c = vdot(oc, oc) - sp->radius2;
    discriminant = (b * b) - (a * c);
    printf ("a : %f, b: %f, c : %f, 판별식 : %f\n", a, b, c, discriminant);

    // 판별식(내적의 값)이 0보다 크다면 광선이 구를 hit한 것!
    // 내적이 양수 : cos 값이 양수, 예각
    // 내적이 0 : cos 값이 0, 직각
    // 내적이 음수 : cos 값이 음수, 둔각
     
     if (discriminant < 0) // 판별식이 0보다 작을 때 : 실근 없을 때,
        return (-1.0);
    else
        return ((-half_b - sqrt(discriminant) / a)); // 두 근 중 작은 근
}