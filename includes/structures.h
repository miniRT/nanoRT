/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 23:26:17 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/16 23:28:40 by kimtaeseon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_vec3		t_vec3;
typedef struct s_vec3		t_point3;
typedef struct s_vec3		t_color3;
typedef struct s_ray		t_ray;
typedef struct s_ambient	t_ambient;
typedef struct s_camera		t_camera;
typedef struct s_object		t_object;
typedef struct s_hit_record	t_hit_record;
typedef struct s_scene		t_scene;
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_light		t_light;
typedef struct s_mlx		t_mlx;
typedef int					t_bool;
typedef int					t_object_type;

# define FALSE 0
# define TRUE 1
# define SP 0
# define PL 1
# define CY 2
# define LIGHT_POINT 3

# define EPSILON 0.000001

# define WIDTH	300
# define HEIGHT	150

struct	s_mlx {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
};

struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

struct s_ambient
{
	t_color3	light_color;
	double		bright_ratio;
};

struct	s_camera
{
	t_point3	origin;
	t_vec3		dir;
	t_vec3		right_normal;
	t_vec3		up_normal;
	t_point3	left_bottom;
	double		fov;
	double		focal_len;
};

struct s_light
{
	t_point3	origin;
	t_color3	light_color;
	double		bright_ratio;
};

struct s_object
{
	t_object_type	type;
	void			*element;
	void			*next;
	t_color3		albedo;

};

struct	s_sphere
{
	t_point3	center;
	double		radius;
	double		radius2;
};

struct s_plane
{
	t_point3	center;
	t_vec3		dir;
};

struct s_cylinder
{
	t_point3	center;
	t_vec3		dir;
	double		diameter;
	double		height;
};

struct	s_ray
{
	t_point3	origin;
	t_vec3		dir;
};

struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		tmin;
	double		tmax;
	double		t;
	t_bool		front_face;
	t_color3	albedo;
};

struct s_scene
{
	t_ambient		ambient;
	t_camera		camera;
	t_object		*world;
	t_object		*light;
	t_ray			ray;
	t_hit_record	rec;
};

#endif
