/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 20:24:49 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/16 11:04:46 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/print.h"
#include "../includes/scene.h"
#include "../includes/trace.h"
#include "shared.h"
#include <stdio.h>
#include <fcntl.h>
#include "../mlx/mlx.h"

// static void print_vec(t_vec3 vec)
// {
// 	printf ("x : %f, y : %f, z : %f\n", vec.x, vec.y, vec.z);
// }

double ft_pow(double base, int exponent)
{
	int	i;
	double result;

	i = 1;
	result = 1;
	while (i <= exponent)
	{
		result = result * base;
		i++;
	}
	return result;
}

double	ft_atof(char *src)
{
	int	i;
	int	sign;
	int	num;
	int pointer;
	double	decimal_point;

	i = 1;
	sign = 1;
	num = 0;
	pointer = 0;
	decimal_point = 0;
	while (ft_isspace(*src))
		src++;
	while (*src)
	{
		if (*src ==  '-')
			sign = -1;
		else if (!pointer && ft_isdigit(*src))
			num = (num * 10) + (*src - '0');
		else if (*src == '.')
			pointer = 1;
		else if (pointer && ft_isdigit(*src))
		{
			decimal_point  = (*src - '0') * ft_pow(0.1, i) + decimal_point;
			i++;
		}
		src++;
	}
	return (sign * (num + decimal_point));
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void			my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// esc key press event
int	key_hook(int keycode, t_mlx *mlx)
{
	(void) mlx;
	if (keycode == 53)
		exit(1);
	return (0);
}

int	red_button(int key_num, t_mlx *mlx)
{
	(void)key_num;
	(void)mlx;
	exit(1);
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
	vec.x = ft_atof(info[0]);
	vec.y = ft_atof(info[1]);
	vec.z = ft_atof(info[2]);
	return (vec);
}

void	validator_value(char *message, double value, double min, double max)
{
	if (value < min || value > max)
	{
		ft_putstr_fd(message, STDERR_FILENO);
		exit(1);
	}
}

void	validator_color(t_color3 value, double min, double max)
{
	validator_value("Not valid light R value", value.x, min, max);
	validator_value("Not valid light G value", value.y, min, max);
	validator_value("Not valid light B value", value.z, min, max);
}

void	validator_vector(t_vec3 value, double min, double max)
{
	validator_value("Not valid value", value.x, min, max);
	validator_value("Not valid value", value.y, min, max);
	validator_value("Not valid value", value.z, min, max);
}

void	ambient_value_setter(t_ambient *ambient, char *input)
{
	double		bright_ratio;
	t_color3	light_color;
	char **info;

	info = ft_split(input, ' ');
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

	char **info;

	info = ft_split(input, ' ');
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

	char	**info;

	info = ft_split(input, ' ');

	origin = parse_vec(info[1]);
	bright_ratio = ft_atof(info[2]);
	validator_value("Not valid bright_ratio value", bright_ratio, 0.0, 1.0);
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
	diameter = ft_atof(info[2]);
	albedo = parse_vec(info[3]);
	validator_color(albedo, 0, 255);
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
	validator_vector(dir, -1, 1);
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
	validator_vector(dir, -1, 1);
	diameter = ft_atof(info[3]);
	height = ft_atof(info[4]);
	albedo = parse_vec(info[5]);
	validator_color(albedo, 0, 255)	;
	oadd(world, object(CY, cylinder(origin, dir, diameter, height), albedo));
}

void	environment_value_setter(t_scene *scene, char *input)
{
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
// 기본 세팅

static void	mlx_initialize(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "miniRT");
  	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT); // 이미지 객체 생성
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian); // 이미지 주소 할당

	mlx_key_hook(mlx->win, key_hook, &mlx); // esc key press event
	mlx_hook(mlx->win, 17, 0, red_button, &mlx);
}

static void raytracing(t_scene *scene, t_mlx *mlx)
{
	int     i; // x
	int     j; // y
	t_color3    pixel_color;

	j = HEIGHT - 1;
	while (j >= 0)
	{
		i = 0;
	   while (i < WIDTH)
		{
			printf ("x : %d y : %d\n", i, j);
			scene->ray = ray_primary(&scene->camera, i, j);
			// print_vec(scene->ray.dir);
			pixel_color = ray_color(scene);
			// write_color(pixel_color);
			my_mlx_pixel_put(mlx, i, HEIGHT - 1 - j, create_trgb(0, pixel_color.x, pixel_color.y, pixel_color.z));
			// y축(j)를 반전시켜서 구현
			++i;
		}
		--j;
	}
}

int	main(int argc, char **argv)
{
	(void)argc;
	t_scene *scene;
	t_mlx	mlx;
	if (argc == 1)
		return (-1);
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
		// free(str);
		str = 0;
	}
	// printf("✅%f\n", ft_pow(0.1, 10));




	// while (scene->world)
	// {
	// 	print_vec(scene->world->albedo);
	// 	scene->world = scene->world->next;
	// }
			// print_vec(scene->camera.dir);
	init_camera(&scene->camera);
	mlx_initialize(&mlx);
	raytracing(scene, &mlx);

	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx);
}

// 분기 확실하게 분기
// atof 만들어서 사용
// 유효값 검사
// 파싱 스페이스 여러개 있어도 정상적으로 감지?
