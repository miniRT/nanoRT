/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 23:11:22 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/17 15:49:46 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "utils.h"
#include "scene.h"

t_vec3	parse_vec(char *str)
{
	char	**info;
	t_vec3	vec;

	info = ft_split(str, ',');
	if (ft_get_count_of_list(info) != 3)
	{
		ft_putstr_fd("Format is not Valid", STDERR_FILENO);
		ft_exit(1);
	}
	vec.x = ft_atof(info[0]);
	vec.y = ft_atof(info[1]);
	vec.z = ft_atof(info[2]);
	return (vec);
}

void	sphere_value_setter(t_object **world, char *input)
{
	t_vec3		origin;
	float		diameter;
	t_color3	albedo;
	char		**info;

	info = ft_split(input, ' ');
	if (ft_get_count_of_list(info) != 4)
	{
		ft_putstr_fd("Format is not Valid", STDERR_FILENO);
		ft_exit(1);
	}
	origin = parse_vec(info[1]);
	diameter = ft_atof(info[2]);
	albedo = parse_vec(info[3]);
	validator_color(albedo, 0, 255);
	oadd(world, object(SP, sphere(origin, diameter), albedo));
}

void	plane_value_setter(t_object **world, char *input)
{
	t_vec3		origin;
	t_vec3		dir;
	t_color3	albedo;
	char		**info;

	info = ft_split(input, ' ');
	if (ft_get_count_of_list(info) != 4)
	{
		ft_putstr_fd("Format is not Valid", STDERR_FILENO);
		ft_exit(1);
	}
	origin = parse_vec(info[1]);
	dir = parse_vec(info[2]);
	validator_vector(dir, -1, 1);
	albedo = parse_vec(info[3]);
	oadd(world, object(PL, plane(origin, dir), albedo));
}

void	cylinder_value_setter(t_object **world, char *input)
{
	t_vec3		origin;
	t_vec3		dir;
	double		diameter;
	double		height;
	char		**info;

	info = ft_split(input, ' ');
	if (ft_get_count_of_list(info) != 6)
	{
		ft_putstr_fd("Format is not Valid", STDERR_FILENO);
		ft_exit(1);
	}
	origin = parse_vec(info[1]);
	dir = parse_vec(info[2]);
	validator_vector(dir, -1, 1);
	diameter = ft_atof(info[3]);
	height = ft_atof(info[4]);
	validator_color(parse_vec(info[5]), 0, 255);
	oadd(world, object(CY, cylinder(origin, dir, diameter, height),
			parse_vec(info[5])));
}

void	environment_value_setter(t_scene *scene, char *input)
{
	if (!check_valid_identifier(input))
	{
		ft_putstr_fd("Error\n Invalid Identifier", STDERR_FILENO);
		ft_exit(1);
	}
	if (input[0] == 'A')
		ambient_value_setter(&scene->ambient, input);
	else if (input[0] == 'C')
		camera_value_setter(&scene->camera, input);
	else if (input[0] == 'L')
		light_value_setter(&scene->light, input);
	else if (input[0] == 's' && input[1] == 'p')
		sphere_value_setter(&scene->world, input);
	else if (input[0] == 'p' && input[1] == 'l')
		plane_value_setter(&scene->world, input);
	else if (input[0] == 'c' && input[1] == 'y')
		cylinder_value_setter(&scene->world, input);
}
