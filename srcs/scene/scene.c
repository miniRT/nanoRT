/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:17:53 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/15 22:15:21 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/scene.h"

// t_camera	camera(t_canvas *canvas, t_point3 orig)
// {
// 	t_camera	cam;
// 	double		focal_len;
// 	double		viewport_height;

// 	viewport_height = 2.0;
// 	focal_len = 1.0;
// 	cam->origin = orig;
// 	cam->viewport_h = viewport_height;
// 	cam->viewport_w = viewport_height * canvas->aspect_ratio;
// 	cam->focal_len = focal_len;
// 	cam->horizontal = vec3(cam->viewport_w, 0, 0);
// 	cam->vertical = vec3(0, cam->viewport_h, 0);
// 	cam->left_bottom = vminus(vminus(vminus(cam->origin,
// 					vdivide(cam->horizontal, 2)),
// 				vdivide(cam->vertical, 2)),
// 			vec3(0, 0, focal_len));
// 	return (cam);
// }


// static void print_vec(t_vec3 vec)
// {
// 	printf ("x : %f, y : %f, z : %f\n", vec.x, vec.y, vec.z);
// }


static float	get_tan(float degree)
{
	static const float	radian = M_PI / 180;

	return (tan(degree * radian));
}


void init_camera(t_camera *cam)
{
    t_vec3      vec_y;
    t_vec3      vec_z;
    t_vec3      temp;

	vec_y = vec3(0.0, 1.0, 0.0);
    vec_z = vec3(0.0, 0.0, -1.0);

    if (vlength(vcross(vec_y, cam->dir)))
        cam->right_normal = vunit(vcross(cam->dir, vec_y));
    else
        cam->right_normal = vunit(vcross(cam->dir, vec_z));
    cam->up_normal = vunit(vcross(cam->right_normal, cam->dir));
    cam->focal_len = (float)WIDTH / 2 / get_tan(cam->fov / 2);

	// printf ("%f\n", cam->focal_len);
    temp = vplus(cam->origin, vmult(cam->dir, cam->focal_len));
    temp = vminus(temp, vmult(cam->right_normal, (float)(WIDTH - 1)/ 2));
    temp = vminus(temp, vmult(cam->up_normal, (float)(HEIGHT - 1)/ 2));
    cam->left_bottom = temp;
    // print_vec(cam->right_normal);
    // print_vec(cam->up_normal);
    // print_vec(cam->left_bottom);
}
