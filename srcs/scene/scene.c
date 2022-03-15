/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:17:53 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/15 11:46:18 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/scene.h"

t_camera	camera(t_canvas *canvas, t_point3 orig)
{
	t_camera	cam;
	double		focal_len;
	double		viewport_height;

	viewport_height = 2.0;
	focal_len = 1.0;
	cam.origin = orig;
	cam.viewport_h = viewport_height;
	cam.viewport_w = viewport_height * canvas->aspect_ratio;
	cam.focal_len = focal_len;
	cam.horizontal = vec3(cam.viewport_w, 0, 0);
	cam.vertical = vec3(0, cam.viewport_h, 0);
	cam.left_bottom = vminus(vminus(vminus(cam.origin,
					vdivide(cam.horizontal, 2)),
				vdivide(cam.vertical, 2)),
			vec3(0, 0, focal_len));
	return (cam);
}
