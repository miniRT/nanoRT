#include "structures.h"
#include "utils.h"
#include "trace.h"

// static void print_vec(t_vec3 vec3)
// {
//     printf ("x : %f, y : %f, z : %f\n", vec3.x, vec3.y, vec3.z);
// }


double		cy_boundary(t_cylinder *cy, t_vec3 at_point)
{
    double	hit_height;
	double	max_height;

    hit_height = vdot(vminus(at_point, cy->center), cy->dir);
    max_height = cy->height / 2;

    if (fabs(hit_height) > max_height)
		return (0);

	return (hit_height);
}

t_vec3      get_cylinder_normal(t_cylinder *cy, t_vec3 at_point, double hit_height)
{
    t_point3 hit_center;
    t_vec3 normal;

    hit_center = vplus(cy->center, vmult(cy->dir, hit_height));
    normal = vminus(at_point, hit_center);

    return (vunit(normal));
}

int      hit_cylinder_cap(t_object *cy_obj, t_ray *ray, t_hit_record *rec, double height)
{
    const t_cylinder *cy = cy_obj->element;
    const double r = cy->diameter / 2;
    const t_vec3    circle_center = vplus(cy->center, vmult(cy->dir, height));
    const float root = vdot(vminus(circle_center, ray->origin), cy->dir) \
    / vdot(ray->dir, cy->dir); // 광선ㅇ
    const float diameter = vlength(vminus(circle_center, ray_at(ray, root)));
	if (fabs(r) < fabs(diameter))
		return (0);
    if (root < rec->tmin || rec->tmax < root)
       return (0);
    rec->t = root; 
    rec->p = ray_at(ray, root);
    rec->tmax = rec->t;
    if (0 < height)
        rec->normal = cy->dir;
    else
        rec->normal = vmult(cy->dir, -1);

    // rec->normal = vunit(vminus(circle_center, ray->origin)); // vmult(ray->dir, root)하면 안돼!!!
    set_face_normal(ray, rec);
    rec->albedo = cy_obj->albedo;
    return (1);
}

int      hit_cylinder_side(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
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
    double hit_height;
    
    cy = cy_obj->element;
    u = ray->dir;
    o = cy->dir;
    r = cy->diameter / 2;
    delta_P = vminus(ray->origin, cy->center);
    a = vlength2(vcross(u, o));
    half_b = vdot(vcross(u, o), vcross(delta_P, o));
    c = vlength2(vcross(delta_P, o)) - pow(r, 2);
    discriminant = half_b * half_b - a * c;
    if (discriminant < 0) 
        return (0);
    // 이 시점에서 판별식이 참이 나왔기에 근이 존재한다고 판단한다.
    sqrtd = sqrt(discriminant); 
    root = (-half_b - sqrtd) / a;  // 근의 공식 해, 작은 근부터 고려.
    if (root < rec->tmin || rec->tmax < root)
    {
    root = (-half_b + sqrtd) / a; 
        if (root < rec->tmin || rec->tmax < root)
        return (0);
    }
    //    print_vec(vmult(ray->dir, root));
    // print_vec(ray_at(ray, root));
    if (!(hit_height = cy_boundary(cy, ray_at(ray, root))))
        return (0);

    rec->t = root; // 광선의 원점과 교점까지의 거리를 rec에 저장한다.
    rec->p = ray_at(ray, root); // 교점의 좌표를 rec에 저장한다.
    // rec->normal = get_cylinder_normal(cy, vmult(ray->dir, root), hit_height);
    rec->normal = get_cylinder_normal(cy, rec->p, hit_height); // vmult(ray->dir, root)하면 안돼!!!
    set_face_normal(ray, rec); // 카메라가 구의 안쪽에 있을 경우 광선과 법선은 같은 방향을 향하게 된다. 법선과 광선이 반대방향을 향햐도록 확인하는 함수를 추가했다.
    // normal length 이상(반지름 이상)
    // 충돌지점이 카메라 반대쪽 일수도
    // 가장 가까운 포인트를 못잡음
    rec->albedo = cy_obj->albedo;
    return (1);
}

t_bool      hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
    const t_cylinder *cy = cy_obj->element;
    int result;

    result = 0;
    result += hit_cylinder_cap(cy_obj, ray, rec, cy->height / 2);
    result += hit_cylinder_cap(cy_obj, ray, rec, -(cy->height / 2));
    result += hit_cylinder_side(cy_obj, ray, rec);
    return (result);
}