#include "structures.h"
#include "utils.h"
#include "trace.h"

// static void print_vec(t_vec3 vec3)
// {
//     printf ("x : %f, y : %f, z : %f\n", vec3.x, vec3.y, vec3.z);
// }


int		cy_boundary(t_cylinder *cy, t_vec3 at_point)
{
    t_vec3  hit_ray;

	double	max_len;
    double	hit_len;

    hit_ray = vminus(at_point, cy->point);
	max_len = cy->height / 2;

    hit_len = vdot(hit_ray, cy->normal);
    printf("max_len : %f, hit_len : %f", max_len, hit_len);
	if (hit_len < 0)
        hit_len = -hit_len;
    if (hit_len > max_len)
		return (-1);

    printf ("hit!\n");
	return (0);
}

t_bool      hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
    t_cylinder *cy;

    // t_vec3  A;
    // t_vec3  B;
    // double  r;
    //a, b, c는 각각 t에 관한 근의 공식 2차 방정식의 계수
    double  a;
	double  half_b;
    double  c;
    t_vec3  u;
    t_vec3  o;
    t_vec3  delta_P;
    double r;

    double discriminant; // 판별식
    double sqrtd;
    double root;

  // honlee님 코드
// cy = cy_obj->element;
// A = vminus(ray->dir, vmult(cy->normal, vdot(ray->dir, cy->normal)));
// B = vminus(ray->orig, cy->point);
// B = vminus(B, vmult(cy->normal, vdot(ray->orig, cy->normal)));
// B = vplus(B, vmult(cy->normal, vdot(cy->point, cy->normal)));
// r = cy->diameter / 2;
// a = vdot(A, A);
// b = vdot(vmult(A, 2.0), B);
// c = vdot(B, B) - pow(r, 2);
// discriminant = b * b - (a * c * 4);
  // jseo님 코드
    cy = cy_obj->element;
    u = ray->dir;
    o = cy->normal;
    r = cy->diameter / 2;
    delta_P = vminus(ray->orig, cy->point);
    a = vlength2(vcross(u, o));
    half_b = vdot(vcross(u, o), vcross(delta_P, o));
    c = vlength2(vcross(delta_P, o)) - pow(r, 2);
    discriminant = half_b * half_b - a * c;
    printf ("판별식 : %f\n", discriminant);
    if (discriminant < 0) 
        return (FALSE);
    // 이 시점에서 판별식이 참이 나왔기에 근이 존재한다고 판단한다.
    sqrtd = sqrt(discriminant); 
    root = (-half_b - sqrtd) / a;  // 근의 공식 해, 작은 근부터 고려.
    if (root < rec->tmin || rec->tmax < root)
    {
    root = (-half_b + sqrtd) / a; 
        if (root < rec->tmin || rec->tmax < root)
        return (FALSE);
    }
    if (cy_boundary(cy, vmult(ray->dir, root)))
        return (FALSE);
    rec->t = root; // 광선의 원점과 교점까지의 거리를 rec에 저장한다.
    rec->p = ray_at(ray, root); // 교점의 좌표를 rec에 저장한다.
    rec->albedo = cy_obj->albedo;
    return (TRUE);
}
