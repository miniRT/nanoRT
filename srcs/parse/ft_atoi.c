/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 19:17:30 by sham              #+#    #+#             */
/*   Updated: 2022/03/16 22:30:14 by kimtaeseon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

int	ft_atoi(const char *str)
{
	long	sign;
	long	num;

	sign = 1;
	num = 0;
	while (*str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r' || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		num = 10 * num + (*str - '0');
		str++;
		if (num > 2147483647 && sign == 1)
			return (-1);
		if (num < -2147483648 && sign == -1)
			return (0);
	}
	return ((int)(num * sign));
}
