/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 23:11:22 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/18 12:41:23 by sham             ###   ########.fr       */
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
		free_all(info);
		ft_exit(1);
	}
	vec.x = ft_atof(info[0]);
	vec.y = ft_atof(info[1]);
	vec.z = ft_atof(info[2]);
	free_all(info);
	return (vec);
}

void	sphere_value_setter(t_object **world, char *input)
{
	t_vec3		origin;
	float		diameter;
	t_color3	color;
	char		**info;

	info = ft_split(input, ' ');
	if (ft_get_count_of_list(info) != 4)
	{
		ft_putstr_fd("Format is not Valid", STDERR_FILENO);
		free_all(info);
		ft_exit(1);
	}
	origin = parse_vec(info[1]);
	diameter = ft_atof(info[2]);
	color = parse_vec(info[3]);
	validator_color(color, 0, 255);
	oadd(world, object(SP, sphere(origin, diameter), color));
	free_all(info);
}

void	plane_value_setter(t_object **world, char *input)
{
	t_vec3		origin;
	t_vec3		dir;
	t_color3	color;
	char		**info;

	info = ft_split(input, ' ');
	if (ft_get_count_of_list(info) != 4)
	{
		ft_putstr_fd("Format is not Valid", STDERR_FILENO);
		free_all(info);
		ft_exit(1);
	}
	origin = parse_vec(info[1]);
	dir = parse_vec(info[2]);
	validator_vector(dir, -1, 1);
	color = parse_vec(info[3]);
	oadd(world, object(PL, plane(origin, dir), color));
	free_all(info);
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
		free_all(info);
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
	free_all(info);
}

void	environment_value_setter(t_scene *scene,
		char *input, t_input_checker *input_checker)
{
	if (!check_valid_identifier(input))
		error_disposal("Error\n Invalid Identifier");
	if (input[0] == 'A')
	{
		input_checker->a_count++;
		ambient_value_setter(&scene->ambient, input);
	}
	else if (input[0] == 'C')
	{
		input_checker->c_count++;
		camera_value_setter(&scene->camera, input);
	}
	else if (input[0] == 'L')
	{
		input_checker->l_count++;
		light_value_setter(&scene->light, input);
	}
	else if (input[0] == 's' && input[1] == 'p')
		sphere_value_setter(&scene->world, input);
	else if (input[0] == 'p' && input[1] == 'l')
		plane_value_setter(&scene->world, input);
	else if (input[0] == 'c' && input[1] == 'y')
		cylinder_value_setter(&scene->world, input);
}
