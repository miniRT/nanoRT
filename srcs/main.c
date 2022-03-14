/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 20:24:49 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/14 21:18:25 by kimtaeseon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/print.h"
#include "../includes/scene.h"
#include "../includes/trace.h"
#include "shared.h"
#include <stdio.h>
#include <fcntl.h>

// void	file_open(char *path)
// {
// 	int		fd;
// 	char	*str;

// 	str = 0;
// 	fd = open(path, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		exit(1);
// 	}
// 	else
// 	{
// 		ft_get_next_line(fd, &str);
// 		printf("✅%s\n", str);
// 	}
// }

void	ambient_value_setter(t_color3 ambient, char *input)
{
	char	**arguments;

	arguments = ft_split(input, '5');
	printf("%s\n", arguments[0]);
	// ambient.x =
	// ambient.y =
	// ambient.z =

	(void)ambient;
}


void	environment_value_setter(t_scene *scene, char *input)
{
	(void)scene;
	printf ("%s\n", input);
	// if (input[0] == 'A')
	// 	ambient_value_setter(scene->ambient, input);
	if (input[0] == 'A')
		ambient_value_setter(scene->ambient, input);
	// else if (input[0] == 'c')
	// 	camera_value_setter(scene->camera, input);
	// else if (input[0] == 'l')
	// 	light_value_setter(scene->light, input);
	// else if (input[0] == 's')
	// 	object_value_setter(scene->world, input);
	// else if (input[0] == 'p')
	// 	object_value_setter(scene->world, input);
	// else if (input[0] == 'c')
	// 	object_value_setter(scene->world, input);
}



// void camera_value_setter(t_camera camera, char *input)
// {

// }
// void light_value_setter(t_object *light, char *input)
// {

// }

// void object_value_setter(t_object *world, char *input)
// {

// }

int	main(int argc, char **argv)
{
	// t_color3	pixel_color;
	// t_canvas	canv;
	// t_camera	cam;
	// t_ray		ray;
	// int			i;
	// int			j;
	// double		u;
	// double		v;
	(void)argc;

	t_scene scene;
	int		fd;
	int		ret;
	char	*str;

	ret = 1;
	str = 0;
	// scene_init(scene);
	fd = file_open(argv[1]);
	while (ret != 0)
	{
		ret = ft_get_next_line(fd, &str);
		if (ret < 0)
		{
			write(STDERR_FILENO, "ERROR\n", 6);
			exit(1);
		}
		environment_value_setter(&scene, str);
		free(str);
		str = 0;
	}
	// canv = canvas(400, 300);
	// cam = camera(&canv, point3(0, 0, 0));
	// printf("P3\n%d %d\n255\n", canv.width, canv.height);
	// j = canv.height - 1;
	// while (j >= 0)
	// {
	// 	i = 0;
	// 	while (i < canv.width)
	// 	{
	// 		u = (double)i / (canv.width - 1);
	// 		v = (double)j / (canv.height - 1);
	// 		ray = ray_primary(&cam, u, v);
	// 		pixel_color = ray_color(&ray);
	// 		write_color(pixel_color);
	// 		++i;
	// 	}
	// 	--j;
	// }
}
