/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 23:38:26 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/17 15:43:21 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/print.h"
#include "utils.h"
#include "../mlx/mlx.h"
#include <stdlib.h>

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length
			+ x * (mlx->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	key_hook(int keycode, t_mlx *mlx)
{
	(void) mlx;
	if (keycode == 53)
		ft_exit(1);
	return (0);
}

int	red_button(int key_num, t_mlx *mlx)
{
	(void)key_num;
	(void)mlx;
	ft_exit(1);
	return (0);
}
