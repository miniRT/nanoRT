/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:55:36 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/15 16:30:14 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/trace.h"

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

    ray.origin = cam->origin; // 0, 0, 0
    // left_bottom + (u * horizontal) + (v * vertical) - origin 의 단위 벡터.
    horizontal = vmult(cam->right_normal, x);
    vertical = vmult(cam->up_normal, y);
    
    ray_vec = cam->left_bottom;
    ray_vec = vplus(ray_vec, horizontal);
    ray_vec = vplus(ray_vec, vertical);               

    ray_vec = vminus(ray_vec, cam->origin); // 0, 0, 0. 의미가 없는데? 카메라가 변경될 때를 고려한 건가?
                // printf ("minus : "); // 이 시점에서 가로와 세로의 벡터 합 계산이 완료되었다.
                // print_vec(unitvect); 
    ray_vec = vunit(ray_vec);
                // printf ("단위 백터 : ");
                // print_vec(unitvect); // 해당 뷰포트의 단위 백터, 가리키는 방향
    ray.dir = ray_vec;
	return (ray);
}

t_color3	ray_color(t_ray *r)
{
	double	t;

	t = 0.5 * (r->dir.y + 1.0);
	return (vplus(vmult(color3(1, 1, 1), 1.0 - t),
			vmult(color3(0.5, 0.7, 1.0), t)));
}
