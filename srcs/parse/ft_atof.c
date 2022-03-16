/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 23:12:48 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/16 23:37:00 by kimtaeseon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

double	ft_pow(double base, int exponent)
{
	double	result;
	int		i;

	i = 1;
	result = 1;
	while (i <= exponent)
	{
		result = result * base;
		i++;
	}
	return (result);
}

double	ft_atof(char *src)
{
	int		i;
	int		sign;
	int		num;
	int		pointer;
	double	decimal_point;

	i = 1;
	sign = 1;
	num = 0;
	pointer = 0;
	decimal_point = 0;
	while (ft_isspace(*src))
		src++;
	while (*src)
	{
		if (*src == '-')
			sign = -1;
		else if (!pointer && ft_isdigit(*src))
			num = (num * 10) + (*src - '0');
		else if (*src == '.')
			pointer = 1;
		else if (pointer && ft_isdigit(*src))
		{
			decimal_point = (*src - '0') * ft_pow(0.1, i) + decimal_point;
			i++;
		}
		src++;
	}
	return (sign * (num + decimal_point));
}
