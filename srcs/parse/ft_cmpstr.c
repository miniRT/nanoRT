/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmpstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 16:10:29 by sham              #+#    #+#             */
/*   Updated: 2022/03/16 22:30:18 by kimtaeseon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

int	ft_cmpstr(char *str1, char *str2)
{
	int		i;

	i = 0;
	while (str1[i])
	{
		if (str1[i] != str2[i])
			return (-1);
		i++;
	}
	if (str2[i])
		return (-1);
	return (0);
}
