/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:42:33 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/17 18:41:45 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include "scene.h"
#include "trace.h"
#include "shared.h"
#include "structures.h"
// #include <mlx.h>
#include "../mlx/mlx.h"
#include <stdio.h>
#include <fcntl.h>

static void	mlx_initialize(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "miniRT");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img,
			&mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	mlx_key_hook(mlx->win, key_hook, &mlx);
	mlx_hook(mlx->win, 17, 0, red_button, &mlx);
}

static void	raytracing(t_scene *scene, t_mlx *mlx)
{
	int			i;
	int			j;
	t_color3	pixel_color;

	j = HEIGHT - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < WIDTH)
		{
			scene->ray = ray_primary(&scene->camera, i, j);
			pixel_color = ray_color(scene);
			my_mlx_pixel_put(mlx, i, HEIGHT - 1 - j,
				create_trgb(0, pixel_color.x, pixel_color.y, pixel_color.z));
			++i;
		}
		--j;
	}
}

void	space_converter(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_isspace_mini(input[i]))
			input[i] = ' ';
		i++;
	}
}

void	scene_value_setter(t_scene *scene, char *input)
{
	int				fd;
	int				ret;
	char			*str;
	t_input_checker	input_checker;

	ret = 1;
	str = 0;
	fd = file_open(input);
	input_checker_init(&input_checker);
	while (ret != 0)
	{
		ret = ft_get_next_line(fd, &str);
		if (ret < 0)
			error_disposal("ERROR\n");
		space_converter(str);
		environment_value_setter(scene, str, &input_checker);
		if (input_checker.a_count > 1
			|| input_checker.c_count > 1 || input_checker.l_count > 1)
			error_disposal("Error\n Invalid Input");
		free(str);
		str = 0;
	}
	if (!input_checker.a_count
		|| !input_checker.c_count || !input_checker.l_count)
		error_disposal("Error\n Invalid Input");
}

int	main(int argc, char **argv)
{
	t_scene	*scene;
	t_mlx	mlx;

	if (argc == 1)
	{
		error_disposal("Error\n No Argument");
		return (-1);
	}
	scene = (t_scene *)malloc(sizeof(t_scene));
	if (!(scene))
		return (-1);
	scene->world = NULL;
	scene->light = NULL;
	rt_finder(argc, argv);
	scene_value_setter(scene, argv[1]);
	init_camera(&scene->camera);
	mlx_initialize(&mlx);
	raytracing(scene, &mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx);
}
