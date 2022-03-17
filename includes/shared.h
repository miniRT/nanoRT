/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:10:37 by sham              #+#    #+#             */
/*   Updated: 2022/03/17 18:10:41 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <time.h>
# include "env.h"
# include "structures.h"

// libft
int				ft_isdigit(char c);
int				ft_strlen(const char *s);
void			*ft_memset(void *b, int c, int len);
void			*ft_calloc(size_t count, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
char			*ft_strdup(char *s);
void			ft_putstr_fd(char *s, int fd);
char			*ft_strjoin(char *s1, char *s2);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_get_next_line(int fd, char **line);
char			*ft_itoa(int n);
int				ft_atoi(const char *str);
int				ft_cmpstr(char *str1, char *str2);

// ts added
int				file_open(char *path);
int				ft_get_next_line(int fd, char **line);
void			*replace(char **out, char *src);
char			*ft_strdup(char *s);
char			*ft_strjoin(char *s1, char *s2);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
int				ft_strlen(const char *s);
char			**ft_split(char const *s, char c);
char			*ft_strndup(const char *src, size_t size);
bool			ft_isspace(int c);
int				ft_isdigit(char c);

t_vec3			parse_vec(char *str);
void			sphere_value_setter(t_object **world, char *input);
void			plane_value_setter(t_object **world, char *input);
void			cylinder_value_setter(t_object **world, char *input);
void			environment_value_setter(t_scene *scene,
					char *input, t_input_checker *input_checker);
void			ambient_value_setter(t_ambient *ambient, char *input);
void			camera_value_setter(t_camera *camera, char *input);
void			light_value_setter(t_object **light, char *input);
double			ft_pow(double base, int exponent);
double			ft_atof(char *src);
void			validator_value(char *message,
					double value, double min, double max);
void			validator_color(t_color3 value, double min, double max);
void			validator_vector(t_vec3 value, double min, double max);
int				create_trgb(int t, int r, int g, int b);
void			my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
int				key_hook(int keycode, t_mlx *mlx);
int				red_button(int key_num, t_mlx *mlx);
bool			ft_isspace_mini(int c);
int				ft_get_count_of_list(char **input);
int				check_valid_identifier(char *input);
void			rt_finder(int argc, char **argv);
int				ft_strcmp(const char *s1, const char *s2);
void			validator_value_fov(char *message,
					double value, double min, double max);
void			free_all(char **input);
void			input_checker_init(t_input_checker *input_checker);
void			error_disposal(char *message);

#endif
