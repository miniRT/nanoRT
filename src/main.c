#include <stdio.h>
#include <mlx.h>

#include "print.h"
#include "scene.h"
#include "structures.h"
#include "trace.h"
#include "utils.h"

typedef struct	s_vars {
	void		*mlx;
	void		*win;
}				t_vars;

typedef struct s_data
{
	void 	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// esc key press event
int	key_hook(int keycode, t_vars *vars)
{
	if(keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}
//
t_scene *scene_init(void)
{
	t_scene		*scene;
	t_object	*world;
	t_object	*lights;
	double		ka;

	if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL);

	scene->canvas = canvas(400, 300);
	scene->camera = camera(&scene->canvas, point3(0, 0, 0));
    world = object(SP, sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0)); // world 에 구1 추가
	oadd(&world, object(SP, sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0))); // world 에 구2 추가
    oadd(&world, object(SP, sphere(point3(0, -1000, 0), 999), color3(1, 1, 1))); // world 에 구3 추가	
	scene->world = world;
	lights = object(LIGHT_POINT, light_point(point3(0, 5, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0));
	// object를 생성하며 세 개의 인자를 받는다. 종류에 해당하는 type, 내용에 해당하는 element, 반사율에 해당하는 albedo.
	// light_point는 광원을 의미하는 t_light 구조체를 리턴한다. t_light는 광원이 위치한 원점인 light_origin, 빛의 색깔인 light_color, 빛의 밝기인 bright_ratio를 인자로 넣어준다.
	// 광원이기에 반사광을 0, 0, 0으로 설정한다.
	scene->light = lights;
	ka = 0.1; 
	scene->ambient = vmult(color3(1,1,1), ka); // 주변광(ambient), 기본적으로 들어가는 빛.
	return (scene);
	// 좌표 평면과 유사, 가운데 0, 0을 기준으로 4분면 
	// x : 좌 우, 음수일 경우 왼쪽, 양수일 경우 오른쪽
	// y : 상 하, 음수일 경우 위, 양수일 경우 아래
	// z : 앞 뒤, 0은 카메라, 줄어들때마다 멀어진다. 양수(카메라의 뒤)일때도 음수와 똑같이 처리됨, 절대값?

}


int	main(void)
{
	int     i;
	int     j;
	double      u;
	double      v;
	t_color3    pixel_color;
	t_scene     *scene;

	t_vars vars;
	t_data image;

	scene = scene_init();

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, scene->canvas.width, scene->canvas.height, "Hello miniRT!"); 
  	image.img = mlx_new_image(vars.mlx, scene->canvas.width, scene->canvas.height); // 이미지 객체 생성
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian); // 이미지 주소 할당
	
	//

	printf("P3\n%d %d\n255\n", scene->canvas.width, scene->canvas.height);
	j = scene->canvas.height - 1;
	while (j >= 0)
	{
		i = 0;
	   while (i < scene->canvas.width)
		{
			u = (double)i / (scene->canvas.width - 1);
			v = (double)j / (scene->canvas.height - 1);
			//ray from camera origin to pixel
			scene->ray = ray_primary(&scene->camera, u, v);
			pixel_color = ray_color(scene);
			write_color(pixel_color);
			my_mlx_pixel_put(&image, i, j, create_trgb(0, pixel_color.x * 255.999, pixel_color.y * 255.999, pixel_color.z * 255.999));
			++i;
		}
		--j;
	}

	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars); // esc key press event
	mlx_loop(vars.mlx);

	return (0);
}