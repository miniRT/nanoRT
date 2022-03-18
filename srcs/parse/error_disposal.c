/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_disposal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:02:30 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/17 17:05:56 by kimtaeseon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "utils.h"

void	error_disposal(char *message)
{
	ft_putstr_fd(message, STDERR_FILENO);
	ft_exit(1);
}
