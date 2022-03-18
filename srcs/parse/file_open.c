/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:48:36 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/17 16:52:45 by kimtaeseon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "utils.h"

int	file_open(char *path)
{
	int		fd;
	char	*str;

	str = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_exit(1);
	return (fd);
}

void	input_checker_init(t_input_checker *input_checker)
{
	input_checker->a_count = 0;
	input_checker->c_count = 0;
	input_checker->l_count = 0;
}
