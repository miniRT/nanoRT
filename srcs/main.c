/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 20:24:49 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/14 22:24:47 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/print.h"
#include "../includes/scene.h"
#include "../includes/trace.h"
#include "shared.h"
#include <stdio.h>
#include <fcntl.h>

static void print_vec(t_vec3 vec)
{
	printf ("x : %f, y : %f, z : %f\n", vec.x, vec.y, vec.z);
}

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


t_vec3 parse_vec(char *str)
{
	char **info;
	t_vec3 vec;

	info = ft_split(str, ',');
	vec.x = atof(info[0]);
	vec.y = atof(info[1]);
	vec.z = atof(info[2]);
	return (vec);
}

void sphere_value_setter(t_object *world, char *input)
{
	t_vec3		origin;
	float		diameter;			
	t_color3	albedo;

	char **info;
	info = ft_split(input, ' ');


	origin = parse_vec(info[1]);
	diameter = atof(info[2]);
	albedo = parse_vec(info[3]);

	// print_vec(origin);
	// printf ("지름 : %f\n", diameter);
	// print_vec(albedo);
	oadd(&world, object(SP, sphere(origin, diameter), albedo));
}

void plane_value_setter(t_object *world, char *input)
{
	t_vec3		origin;
	t_vec3		dir;
	t_color3	albedo;

	char **info;
	info = ft_split(input, ' ');

	origin = parse_vec(info[1]);
	dir = parse_vec(info[2]);
	albedo = parse_vec(info[3]);
	// print_vec(origin);
	// print_vec(albedo);
	oadd(&world, object(PL, plane(origin, dir), albedo));
}

// void cylinder_value_setter(t_object *world, char *input)
// {
// 	t_vec3		origin;
// 	t_vec3		dir;
// 	t_color3	albedo;

// }


void	environment_value_setter(t_scene *scene, char *input)
{
	(void)scene;
	printf ("%s\n", input);
	if (input[0] == 's')
		sphere_value_setter(scene->world, input);
	// if (input[0] == 'A')
	// 	ambient_value_setter(scene->ambient, input);
	if (input[0] == 'A')
		ambient_value_setter(scene->ambient, input);
		if (input[0] == 'p')
		plane_value_setter(scene->world, input);
	// else if (input[0] == 'p')
	// 	plane_value_setter(scene->world, input);
	// else if (input[0] == 'c')
	// 	camera_value_setter(scene->camera, input);
	// else if (input[0] == 'l')
	// 	light_value_setter(scene->light, input);
	// else if (input[0] == 's')
	// 	sphere_value_setter(scene->world, input);
	// else if (input[0] == 'p')
	// 	plane_value_setter(scene->world, input);
	// else if (input[0] == 'c')
	// 	cylinder_value_setter(scene->world, input);
	// while (scene->world->next)
	// {
	// 	printf ("있다!\n");
	// 	scene->world = scene->world->next;
	// }
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
	scene.world = NULL;
	scene.light = NULL;

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
