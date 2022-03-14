/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 20:24:49 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/14 22:04:25 by kimtaeseon       ###   ########.fr       */
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

	arguments = ft_split(input, ' ');
	arguments = ft_split(arguments[2], ',');
	ambient.x = (double) ft_atoi(arguments[0]);
	ambient.y = (double) ft_atoi(arguments[1]);
	ambient.z = (double) ft_atoi(arguments[2]);
}

void	camera_value_setter(t_camera camera, char *input)
{
	char	**arguments;
	char	**origin_template;

	origin_template = 0;
	arguments = 0;
	origin_template = ft_split(input, ' ');
	arguments = ft_split(origin_template[1], ',');
	camera.orig.x = (double) ft_atoi(arguments[0]);
	camera.orig.x = (double) ft_atoi(arguments[0]);
	camera.orig.x = (double) ft_atoi(arguments[0]);
	arguments = ft_split(origin_template[2], ',');
	camera.normal.x = (double) ft_atoi(arguments[0]);
	camera.normal.y = (double) ft_atoi(arguments[0]);
	camera.normal.z = (double) ft_atoi(arguments[0]);
	camera.fov = (double) ft_atoi(origin_template[3]);
}

void	light_value_setter(t_object *light, char *input)
{
	char	**arguments;
	char	**origin_template;

	arguments = 0;
	origin_template = 0;
	origin_template = ft_split(input, ' ');
	arguments = ft_split(origin_template[1], ',');
	light->type = LIGHT_POINT;
	light->albedo.x = (double) ft_atoi(arguments[0]);
	light->albedo.x = (double) ft_atoi(arguments[1]);
	light->albedo.x = (double) ft_atoi(arguments[2]);
}

void	environment_value_setter(t_scene *scene, char *input)
{
	if (input[0] == 'A')
		ambient_value_setter(scene->ambient, input);
	else if (input[0] == 'c')
		camera_value_setter(scene->camera, input);
	else if (input[0] == 'l')
		light_value_setter(scene->light, input);
		// light_value_setter(scene->light, input);
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

// #include <stdio.h>
// #include <mlx.h>
// #include “print.h”
// #include “scene.h”
// #include “structures.h”
// #include “trace.h”
// #include “utils.h”
// typedef struct s_data
// {
//     void    *img;
//     char    *addr;
//     int     bits_per_pixel;
//     int     line_length;
//     int     endian;
// }       t_data;
// typedef struct  s_vars {
//     void        *mlx;
//     void        *win;
//     t_data      image;
// }               t_vars;
// int     create_trgb(int t, int r, int g, int b)
// {
//     return (t << 24 | r << 16 | g << 8 | b);
// }
// void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
//     char    *dst;
//     dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
//     *(unsigned int*)dst = color;
// }
// // esc key press event
// int key_hook(int keycode, t_vars *vars)
// {
//     if(keycode == 53)
//     {
//         mlx_destroy_window(vars->mlx, vars->win);
//         exit(0);
//     }
//     return (0);
// }
// // t_scene *scene_init(void)
// // {
// //  t_scene     *scene;
// //  t_object    *world;
// //  t_object    *lights;
// //  double      ka;
// //  if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
// //      return (NULL);
// //  scene->canvas = canvas(960, 640);
// //  scene->camera = camera(&scene->canvas, point3(0, 0, 0));
// //     world = object(CY, cylinder(point3(0, 0, -5), vec3(-0.5, 1, 0.5), 7, 4), color3(1, 1, 0)); // world 에 구1 추가
// //  // oadd(&world, object(SP, sphere(point3(2,4, 0), 2), color3(1, 0, 0))); // world 에 구2 추가
// //  // oadd(&world, object(SP, sphere(point3(2,-4, 0), 2), color3(0, 0, 1))); // world 에 구2 추가
// //     // oadd(&world, object(PL, plane(point3(-10, 0, -5), vec3(-1, 0, 0)), color3(0, 0, 1)));
// //  // oadd(&world, object(PL, plane(point3(0, -15, -5), vec3(0, -1, 0)), color3(0, 1, 0)));
// //     // oadd(&world, object(PL, plane(point3(0, 0, -10), vec3(0, 0, -1)), color3(1, 0, 0)));
// //     // oadd(&world, object(CY, cylinder(point3(0, 0, 0), vec3(0, 1, 0), 6, 4), color3(0.5, 1, 0)));
// //     // world = object(SP, sphere(point3(3, 0 ,0), 4), color3(0.5, 0, 0.5)); // world 에 구1 추가
// //  scene->world = world;
// //     lights = object(LIGHT_POINT, light_point(point3(10, 0, 1), color3(1, 0.5, 0.5), 0.5), color3(0, 0, 0)); // 더미 albedo
// //  // object를 생성하며 세 개의 인자를 받는다. 종류에 해당하는 type, 내용에 해당하는 element, 반사율에 해당하는 albedo.
// //  // light_point는 광원을 의미하는 t_light 구조체를 리턴한다. t_light는 광원이 위치한 원점인 light_origin, 빛의 색깔인 light_color, 빛의 밝기인 bright_ratio를 인자로 넣어준다.
// //  // 광원이기에 반사광을 0, 0, 0으로 설정한다.
// //  ka = 0.6;
// //  scene->light = lights;
// //  scene->ambient = vmult(color3(1, 1, 1), ka); // 주변광(ambient), 기본적으로 들어가는 빛.
// //  return (scene);
// //  // 좌표 평면과 유사, 가운데 0, 0을 기준으로 4분면
// //  // x : 좌 우, 음수일 경우 왼쪽, 양수일 경우 오른쪽
// //  // y : 상 하, 음수일 경우 위, 양수일 경우 아래
// //  // z : 앞 뒤, 0은 카메라, 줄어들때마다 멀어진다. 양수(카메라의 뒤)일때도 음수와 똑같이 처리됨, 절대값?
// // }
// int main(int argc, char *argv[])
// {
// ////////
//     int     i;
//     int     j;
//     int      canvas_width;
//     int      canvas_height;
//     t_color3    pixel_color;
//     t_scene     *scene;
//     t_vars vars;
//     t_data image;
//     scene = scene_init(argv[1]);
//     image = vars.image;
//     canvas_width = 960;
//     canvas_height = 640;
// ////////
//     vars.mlx = mlx_init();
//     vars.win = mlx_new_window(vars.mlx, canvas_width, canvas_height, “Hello miniRT!“);
//     image.img = mlx_new_image(vars.mlx, canvas_width, canvas_height); // 이미지 객체 생성
//     image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian); // 이미지 주소 할당
//     //
//     // printf(“P3\n%d %d\n255\n”, canvas_width, canvas_height);
//     j = canvas_height - 1;
//     while (j >= 0)
//     {
//         i = 0;
//        while (i < canvas_width)
//         {
//             u = (double)i / (canvas_width - 1);
//             v = (double)j / (canvas_height - 1);
//             //ray from camera origin to pixel
//             scene->ray = ray_primary(&scene->camera, u, v);
//             pixel_color = ray_color(scene);
//             write_color(pixel_color);
//             my_mlx_pixel_put(&image, i, canvas_height - 1 - j, create_trgb(0, pixel_color.x * 255.999, pixel_color.y * 255.999, pixel_color.z * 255.999));
//             // y축(j)를 반전시켜서 구현
//             ++i;
//         }
//         --j;
//     }
//     mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
//     mlx_key_hook(vars.win, key_hook, &vars); // esc key press event
//     mlx_loop(vars.mlx);
//     return (0);
// }
