/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:55:36 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/16 17:06:41 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/trace.h"

// static void print_vec(t_vec3 vec3)
// {
//     printf ("x : %f, y : %f, z : %f\n", vec3.x, vec3.y, vec3.z);
// }


t_ray	ray(t_point3 origin, t_vec3 dir)
{
	t_ray	ray;

	ray.origin = origin;
	ray.dir = vunit(dir);
	return (ray);
}

t_point3	ray_at(t_ray *ray, double t)
{
	t_point3	at;

	at = vplus(ray->origin, vmult(ray->dir, t));
	return (at);
}

t_ray	ray_primary(t_camera *cam, int x, int y)
{
	t_ray   ray;

    t_vec3  horizontal;
    t_vec3  vertical;
    t_vec3  ray_vec;

    ray.origin = cam->origin; 
    horizontal = vmult(cam->right_normal, (double)x);
    vertical = vmult(cam->up_normal, (double)y);
    ray_vec = cam->left_bottom;
    ray_vec = vplus(ray_vec, horizontal);
    ray_vec = vplus(ray_vec, vertical);
    ray_vec = vminus(ray_vec, cam->origin); 
    ray_vec = vunit(ray_vec);
    ray.dir = ray_vec;
    if (x == 250 && y == 125)
        printf ("now!");
	return (ray);
}

t_hit_record record_init(void)
{
    t_hit_record record;

    record.tmin = EPSILON;
    record.tmax = 1000;
    return (record);
}

t_color3	ray_color(t_scene *scene)
{
	scene->rec = record_init();
    // printf ("%f\n", scene->rec.tmin);
    //     printf ("%f\n", scene->rec.tmax);

    if (hit(scene->world, &scene->ray, &scene->rec)) // 모든 구조체에 대한 정보를 담은 연결리스트 world로 광선과의 충돌을 테스트한다.
        return (phong_lighting(scene)); // 법선 벡터를 기반으로 구한 값이 아닌 실제 빛 반사를 계산한 값을 리턴한다.
    else
        return (color3(0, 0, 0));
}
