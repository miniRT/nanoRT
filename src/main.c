#include <stdio.h>
#include <mlx.h>

#include "print.h"
#include "scene.h"
#include "structures.h"
#include "trace.h"
#include "utils.h"
//

typedef struct s_vars {
	void		*mlx;
	void		*win;
}				t_vars;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// esc key press event
int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}
//

int	main(void)
{
	int			i;
	int			j;
	double		u;
	double		v;
	t_color3	pixel_color;
	t_canvas	canv;
	t_camera	cam;
	t_ray		ray;
	t_object	*world;
	t_vars		vars;
	t_data		image;

	canv = canvas(600, 600);
	cam = camera(&canv, point3(0, 0, 0));
	world = object(SP, sphere(point3(-2, 0, -20), 4)); // world 에 구1 추가
	oadd(&world, object(SP, sphere(point3(2, 0, -150),70))); // world 에 구2 추가
	oadd(&world, object(SP, sphere(point3(0, -10, -30), 9))); // world 에 구3 추가
	// 좌표 평면과 유사, 가운데 0, 0을 기준으로 4분면
	// x : 좌 우, 음수일 경우 왼쪽, 양수일 경우 오른쪽
	// y : 상 하, 음수일 경우 위, 양수일 경우 아래
	// z : 앞 뒤, 0은 카메라, 줄어들때마다 멀어진다. 양수(카메라의 뒤)일때도 음수와 똑같이 처리됨, 절대값?

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, canv.width, canv.height, "Hello miniRT!");
  	image.img = mlx_new_image(vars.mlx, canv.width, canv.height); // 이미지 객체 생성
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian); // 이미지 주소 할당
	//
	printf("P3\n%d %d\n255\n", canv.width, canv.height);
	j = canv.height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < canv.width)
		{
			u = (double)i / (canv.width - 1);
			v = (double)j / (canv.height - 1);
			//ray from camera origin to pixel
			ray = ray_primary(&cam, u, v);
			pixel_color = ray_color(&ray, world);
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
