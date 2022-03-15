/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 20:24:49 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/15 11:43:39 by sham             ###   ########.fr       */
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

void	ambient_value_setter(t_ambient *ambient, char *input)
{
	double		bright_ratio;			
	t_color3	light_color;

	char **info;

	info = ft_split(input, ' ');
	bright_ratio = atof(info[1]);
	light_color = parse_vec(info[2]);

	ambient->bright_ratio = bright_ratio;
	ambient->light_color = light_color;
}

void	camera_value_setter(t_camera *camera, char *input)
{
	t_vec3		origin;
	t_vec3		dir;
	double		fov;

	char **info;

	info = ft_split(input, ' ');
	origin = parse_vec(info[1]);
	dir = parse_vec(info[2]);
	fov = atof(info[3]);

	camera->orig = origin;
	camera->normal = dir;
	camera->fov = fov;
}

void	light_value_setter(t_object **light, char *input)
{
	t_vec3		origin;
	double		bright_ratio;			
	t_color3	light_color;

	char	**info;
	
	info = ft_split(input, ' ');
	
	origin = parse_vec(info[1]);
	bright_ratio = atof(info[2]);
	light_color = parse_vec(info[3]);

	*light = object(LIGHT_POINT, light_point(origin, light_color, bright_ratio), color3(0, 0, 0));

}

void sphere_value_setter(t_object **world, char *input)
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
	oadd(world, object(SP, sphere(origin, diameter), albedo));

}

void plane_value_setter(t_object **world, char *input)
{
	t_vec3		origin;
	t_vec3		dir;
	t_color3	albedo;

	char **info;
	info = ft_split(input, ' ');

	origin = parse_vec(info[1]);
	dir = parse_vec(info[2]);
	albedo = parse_vec(info[3]);
	
	oadd(world, object(PL, plane(origin, dir), albedo));
}

void cylinder_value_setter(t_object **world, char *input)
{
	t_vec3		origin;
	t_vec3		dir;
	double		diameter;
	double		height;
	t_color3	albedo;

	char **info;
	info = ft_split(input, ' ');

	origin = parse_vec(info[1]);
	dir = parse_vec(info[2]);
	diameter = atof(info[3]);
	height = atof(info[4]);
	albedo = parse_vec(info[5]);

	oadd(world, object(CY, cylinder(origin, dir, diameter, height), albedo));
}


void	environment_value_setter(t_scene *scene, char *input)
{
	printf ("%s\n", input);
	if (input[0] == 'A')
		ambient_value_setter(&scene->ambient, input);
	else if (input[0] == 'c' && input[1] == ' ')
		camera_value_setter(&scene->camera, input);
	else if (input[0] == 'l')
		light_value_setter(&scene->light, input);
	else if (input[0] == 's')
		sphere_value_setter(&scene->world, input);
	else if (input[0] == 'p')
		plane_value_setter(&scene->world, input);
	else if (input[1] == 'y')
		cylinder_value_setter(&scene->world, input);
	
}

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

	t_scene *scene;

	if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
		return (-1);

	scene->world = NULL;
	scene->light = NULL;

	int		fd;
	int		ret;
	char	*str;

	ret = 1;
	str = 0;

	fd = file_open(argv[1]);
	while (ret != 0)
	{
		ret = ft_get_next_line(fd, &str);
		if (ret < 0)
		{
			write(STDERR_FILENO, "ERROR\n", 6);
			exit(1);
		}
		environment_value_setter(scene, str);
		free(str);
		str = 0;
	}
	// while (scene->world)
	// {
	// 	print_vec(scene->world->albedo); 
	// 	scene->world = scene->world->next;
	// }
			print_vec(scene->ambient.light_color); 
			// print_vec(scene->camera.normal); 


}

// 분기 확실하게 분기
// atof 만들어서 사용
// 유효값 검사