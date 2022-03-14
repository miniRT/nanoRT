#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_vec3 t_vec3; // 백터를 의미한다.
typedef struct s_vec3 t_point3; //  3차원 좌표계 위의 특정 한 점을 의미한다.
typedef struct s_vec3 t_color3; // RGB를 의미한다. x = R, y = G, z = B가 된다. 범위가 0~1 이므로 255.999 를 곱해서 사용한다.
typedef struct s_ray t_ray;

typedef struct s_camera t_camera;
typedef struct s_canvas t_canvas;
typedef struct s_object t_object;
typedef struct s_hit_record t_hit_record;

typedef struct s_scene t_scene;

typedef struct s_sphere t_sphere;
typedef struct s_plane t_plane;
typedef struct s_cylinder t_cylinder;

typedef struct s_light t_light;


typedef int             t_bool;

# define FALSE 0
# define TRUE 1

typedef int t_object_type;

# define SP 0
# define PL 1
# define CY 2
# define LIGHT_POINT 3

# define EPSILON 0.000001 // tmin이 0이 아닌 값을 설정해주기 위해

struct s_vec3
{
	double x;
	double y;
	double z;
};

struct  s_ray
{
	t_point3    orig;
	t_vec3      dir;
};

// struct  s_camera
// {
// 	t_point3    orig;  // 카메라 원점(위치)
// 	t_vec3      normal; // 카메라 벡터
// 	double		fov;
// 	double      focal_len; // focal length
// 	t_point3    left_bottom; // 왼쪽 아래 코너점
// };

struct	s_camera
{
	double		fov;
	t_vec3		normal; // 카메라 벡터
	t_point3	orig;  // 카메라 원점(위치)
	double		viewport_h; // 뷰포트 세로길이
	double		viewport_w; // 뷰포트 가로길이
	t_vec3		horizontal; // 수평길이 벡터
	t_vec3		vertical; // 수직길이 벡터
	double		focal_len; // focal length
	t_point3	left_bottom; // 왼쪽 아래 코너점
};

struct s_object
{
	t_object_type type;
	void	*element;
	void	*next;
	t_color3    albedo; // 해당 물체의 반사율(빛을 얼마나 잘 반사하는지)

};

struct s_hit_record
{
	t_point3    p; // 교점(충돌 지점)에 대한 좌표.
	t_vec3      normal; // 교점에서 뻗어나온 법선(단위 벡터)
	double      tmin; // 기본 0, 물체가 뒤에 있을 경우에는 감지하지 않는다.
	double      tmax; // 광선의 가시거리, 일정 거리를 벗어나면 감지하지 않는다.
	double      t; // 광선의 원점과 교점 사이의 거리.
	t_bool      front_face;
	t_color3    albedo; // 해당 충돌 지점(물체)의 색상
};

struct s_scene
{
	t_camera		camera;
	t_object		*world;
	t_object		*light;
	t_color3		ambient;
	t_ray			ray;
	t_hit_record	rec;
};

struct s_light
{
	t_point3    origin; //  빛이 위치하는 좌표.
	t_color3    light_color; // 빛의 색깔
	double      bright_ratio;
};

struct  s_sphere
{
	t_point3    center;
	double      radius; // 반지름
	double      radius2; // 반지름의 제곱
};

struct s_plane
{
	t_point3    center; // 평면의 어느 한 지점.
	t_vec3      normal; // 평면이 가리키는 방향, 어떻게 기울여져 있는지
};

struct s_cylinder
{
	t_point3    center;
	t_vec3      normal; // 평면이 가리키는 방향, 어떻게 기울여져 있는지
	float		diameter; // 지름
	float		height; // 높이
};

struct  s_canvas
{
    int     width; //canvas width
    int     height; //canvas height;
    double  aspect_ratio; //종횡비
};

#endif
