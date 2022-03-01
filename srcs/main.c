/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 20:24:49 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/01 17:34:36 by kimtaeseon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/print.h"
#include "../includes/scene.h"
#include "../includes/trace.h"

int	main(void)
{
	t_color3	pixel_color;
	t_canvas	canv;
	t_camera	cam;
	t_ray		ray;
	int			i;
	int			j;
	double		u;
	double		v;

	canv = canvas(400, 300);
	cam = camera(&canv, point3(0, 0, 0));
	printf("P3\n%d %d\n255\n", canv.width, canv.height);
	j = canv.height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < canv.width)
		{
			u = (double)i / (canv.width - 1);
			v = (double)j / (canv.height - 1);
			ray = ray_primary(&cam, u, v);
			pixel_color = ray_color(&ray);
			write_color(pixel_color);
			++i;
		}
		--j;
	}
}
