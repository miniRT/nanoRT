/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 23:10:19 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/17 15:48:10 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "scene.h"

void	ambient_value_setter(t_ambient *ambient, char *input)
{
	double		bright_ratio;
	t_color3	light_color;
	char		**info;

	info = ft_split(input, ' ');
	if (ft_get_count_of_list(info) != 3)
	{
		ft_putstr_fd("Error\nAmbient: Format is not Valid", STDERR_FILENO);
		ft_exit(1);
	}
	bright_ratio = ft_atof(info[1]);
	validator_value("Not valid bright_ratio value", bright_ratio, 0.0, 1.0);
	light_color = parse_vec(info[2]);
	validator_color(light_color, 0, 255);
	ambient->bright_ratio = bright_ratio;
	ambient->light_color = light_color;
}

void	camera_value_setter(t_camera *camera, char *input)
{
	t_vec3		origin;
	t_vec3		dir;
	double		fov;
	char		**info;

	info = ft_split(input, ' ');
	if (ft_get_count_of_list(info) != 4)
	{
		ft_putstr_fd("Error\nCamera: Format is not Valid", STDERR_FILENO);
		ft_exit(1);
	}
	origin = parse_vec(info[1]);
	dir = parse_vec(info[2]);
	fov = ft_atof(info[3]);
	validator_vector(dir, -1, 1);
	validator_value("Not valid FOV value", fov, 0, 180);
	camera->origin = origin;
	camera->dir = dir;
	camera->fov = fov;
}

void	light_value_setter(t_object **light, char *input)
{
	t_vec3		origin;
	double		bright_ratio;
	t_color3	light_color;
	char		**info;

	info = ft_split(input, ' ');
	if (ft_get_count_of_list(info) != 4)
	{
		ft_putstr_fd("Error\nLight: Format is not Valid", STDERR_FILENO);
		ft_exit(1);
	}
	origin = parse_vec(info[1]);
	bright_ratio = ft_atof(info[2]);
	validator_value("Not valid bright_ratio value", bright_ratio, 0.0, 1.0);
	light_color = parse_vec(info[3]);
	*light = object(LIGHT_POINT, light_point(origin,
				light_color, bright_ratio), color3(0, 0, 0));
}

void	rt_finder(int argc, char **argv)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (argc != 2)
	{
		ft_putstr_fd("Not valid input", STDERR_FILENO);
		ft_exit(1);
	}
	else
	{
		if (fd != -1 && ft_strcmp(argv[1], "scene/"))
			return ;
		else
		{
			ft_putstr_fd("Not valid file", STDERR_FILENO);
			ft_exit(1);
		}
	}
}
