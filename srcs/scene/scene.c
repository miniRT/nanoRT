/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:17:53 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/16 18:51:56 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/scene.h"

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

    cam->dir = vunit(cam->dir);
    if (vlength(vcross(vec_y, cam->dir)))
        cam->right_normal = vunit(vcross(cam->dir, vec_y));
    else
        cam->right_normal = vunit(vcross(cam->dir, vec_z));
    cam->up_normal = vunit(vcross(cam->right_normal, cam->dir));
    cam->focal_len = (float)WIDTH / 2 / get_tan(cam->fov / 2);
    temp = vplus(cam->origin, vmult(cam->dir, cam->focal_len));
    temp = vminus(temp, vmult(cam->right_normal, (float)(WIDTH - 1)/ 2));
    temp = vminus(temp, vmult(cam->up_normal, (float)(HEIGHT - 1)/ 2));
    cam->left_bottom = temp;
    // print_vec(cam->right_normal);
    // print_vec(cam->up_normal);
    // print_vec(cam->left_bottom);
}
