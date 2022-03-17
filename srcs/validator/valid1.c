/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 23:08:38 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/17 13:50:01 by kimtaeseon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

void	validator_value(char *message, double value, double min, double max)
{
	if (value < min || value > max)
	{
		ft_putstr_fd(message, STDERR_FILENO);
		exit(1);
	}
}

void	validator_color(t_color3 value, double min, double max)
{
	validator_value("Not valid light R value", value.x, min, max);
	validator_value("Not valid light G value", value.y, min, max);
	validator_value("Not valid light B value", value.z, min, max);
}

void	validator_vector(t_vec3 value, double min, double max)
{
	validator_value("Not valid value", value.x, min, max);
	validator_value("Not valid value", value.y, min, max);
	validator_value("Not valid value", value.z, min, max);
}
