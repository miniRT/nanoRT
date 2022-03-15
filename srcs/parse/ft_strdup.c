/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 02:03:05 by pac-man           #+#    #+#             */
/*   Updated: 2022/03/14 21:21:06 by kimtaeseon       ###   ########.fr       */
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

char	*ft_strndup(const char *src, size_t size)
{
	char	*dst;
	size_t	i;

	dst = malloc(sizeof(char) * (size + 1));
	if (!dst)
		return (0);
	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
