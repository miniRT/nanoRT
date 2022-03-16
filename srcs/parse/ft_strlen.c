/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 11:25:52 by taeskim           #+#    #+#             */
/*   Updated: 2022/03/16 23:43:54 by kimtaeseon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	if (!s || !*s)
		return (0);
	while (s[len])
		len++;
	return (len);
}
