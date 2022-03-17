/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 23:08:38 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/17 16:11:02 by kimtaeseon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "utils.h"

void	validator_value(char *message, double value, double min, double max)
{
	if (value < min || value > max)
	{
		ft_putstr_fd(message, STDERR_FILENO);
		ft_exit(1);
	}
}

void	validator_color(t_color3 value, double min, double max)
{
	validator_value("Invalid light R value", value.x, min, max);
	validator_value("Invalid light G value", value.y, min, max);
	validator_value("Invalid light B value", value.z, min, max);
}

void	validator_vector(t_vec3 value, double min, double max)
{
	validator_value("Invalid value", value.x, min, max);
	validator_value("Invalid value", value.y, min, max);
	validator_value("Invalid value", value.z, min, max);
}

int	ft_get_count_of_list(char **input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	return (i);
}

int	check_valid_identifier(char *input)
{
	if (input[0] == 'A')
		return (1);
	else if (input[0] == 'C')
		return (1);
	else if (input[0] == 'L')
		return (1);
	else if (input[0] == 's' && input[1] == 'p')
		return (1);
	else if (input[0] == 'p' && input[1] == 'l')
		return (1);
	else if (input[0] == 'c' && input[1] == 'y')
		return (1);
	else if (ft_isspace(input[0]) || !input[0])
		return (1);
	return (0);
}
