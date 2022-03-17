/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 23:10:19 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/17 18:24:22 by sham             ###   ########.fr       */
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
		free_all(info);
		ft_exit(1);
	}
	bright_ratio = ft_atof(info[1]);
	validator_value("Not valid bright_ratio value", bright_ratio, 0.0, 1.0);
	light_color = parse_vec(info[2]);
	validator_color(light_color, 0, 255);
	ambient->bright_ratio = bright_ratio;
	ambient->light_color = light_color;
	free_all(info);
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
		free_all(info);
		ft_exit(1);
	}
	origin = parse_vec(info[1]);
	dir = parse_vec(info[2]);
	fov = ft_atof(info[3]);
	validator_vector(dir, -1, 1);
	validator_value_fov("Not valid FOV value", fov, 0, 180);
	camera->origin = origin;
	camera->dir = dir;
	camera->fov = fov;
	free_all(info);
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
		free_all(info);
		ft_exit(1);
	}
	origin = parse_vec(info[1]);
	bright_ratio = ft_atof(info[2]);
	validator_value("Not valid bright_ratio value", bright_ratio, 0.0, 1.0);
	light_color = parse_vec(info[3]);
	*light = object(LIGHT_POINT, light_point(origin,
				light_color, bright_ratio), color3(0, 0, 0));
	free_all(info);
}

void	rt_finder(int argc, char **argv)
{
	int		fd;
	int		len;

	len = 0;
	if (argc != 2)
		error_disposal("Not valid input");
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd != -1)
		{
			len = ft_strlen(argv[1]);
			if (argv[1][len - 4] == '/')
				error_disposal("Not valid file");
			else if (argv[1][len - 3] == '.'
					&& argv[1][len - 2] == 'r' && argv[1][len - 1] == 't' )
				return ;
			else
				error_disposal("Not valid file");
			close(fd);
		}
		else
			error_disposal("Not valid file");
	}
}

int	ft_get_count_of_list(char **input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	return (i);
}
