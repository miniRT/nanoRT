/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:52:09 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/15 16:25:10 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_H
# define TRACE_H

# include "structures.h"
# include "utils.h"

t_ray		ray(t_point3 origin, t_vec3 dir);
t_point3	ray_at(t_ray *ray, double t);
t_ray		ray_primary(t_camera *cam, int x, int y);
t_color3	ray_color(t_ray *r);

#endif
