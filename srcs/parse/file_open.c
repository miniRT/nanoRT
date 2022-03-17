/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:48:36 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/17 15:42:39 by sham             ###   ########.fr       */
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
