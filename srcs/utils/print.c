/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 20:23:27 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/17 11:42:12 by kimtaeseon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/print.h"

void	write_color(t_color3 pixel_color)
{
	printf("%d %d %d\n", (int)(255.999 * pixel_color.x),
		(int)(255.999 * pixel_color.y),
		(int)(255.999 * pixel_color.z));
}
