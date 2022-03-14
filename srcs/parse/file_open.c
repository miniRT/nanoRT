/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:48:36 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/13 17:49:14 by kimtaeseon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

int	file_open(char *path)
{
	int		fd;
	char	*str;

	str = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit(1);
	return (fd);
}
