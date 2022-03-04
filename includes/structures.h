/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 20:21:07 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/03 19:30:11 by kimtaeseon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# define FALSE 0
# define TRUE 1

typedef struct s_vec3	t_vec3;
typedef struct s_vec3	t_point3;
typedef struct s_vec3	t_color3;
typedef struct s_ray	t_ray;
typedef struct s_camera	t_camera;
typedef struct s_canvas	t_canvas;
typedef struct s_sphere	t_sphere;
typedef int				t_bool;

struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

struct s_ray
{
	t_point3	origin;
	t_vec3		dir;
};

struct	s_camera
{
	t_point3	orig;
	double		viewport_h;
	double		viewport_w;
	t_vec3		horizontal;
	t_vec3		vertical;
	double		focal_len;
	t_point3	left_bottom;
};

struct	s_canvas
{
	int		width;
	int		height;
	double	aspect_ratio;
};

struct s_sphere
{
	t_point3	origin;
	double		radius;
	double		radius2;
};

#endif
