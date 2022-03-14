/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 02:03:05 by pac-man           #+#    #+#             */
/*   Updated: 2022/03/13 16:52:05 by kimtaeseon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

char	*ft_strdup(char *s)
{
	size_t	len;
	char	*buf;

	len = ft_strlen(s);
	buf = (char *)malloc(len + 1);
	if (!(buf))
		return (NULL);
	ft_strlcpy(buf, s, len + 1);
	return (buf);
}
