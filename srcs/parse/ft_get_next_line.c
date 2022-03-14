/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 18:26:05 by taeskim           #+#    #+#             */
/*   Updated: 2022/03/13 17:37:08 by kimtaeseon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

void	*make_line(char **line, char *src, size_t offset)
{
	size_t	index;

	index = -1;
	*line = (char *)malloc(offset + 1);
	if (!*line)
		return (*line);
	(*line)[offset] = 0;
	while (src[++index] && src[index] != '\n')
		(*line)[index] = src[index];
	ft_strlcpy(src, src + offset + 1, ft_strlen(src) - offset);
	return (*line);
}

int	read_exist(char **line, char *src)
{
	size_t	offset;

	offset = -1;
	while (src[++offset])
	{
		if (src[offset] == '\n')
		{
			if (!make_line(line, src, offset))
				return (-1);
			return (1);
		}
	}
	return (0);
}

int	read_new(char **line, char **src, int fd)
{
	size_t	offset;
	int		read_size;
	char	buff[BUFFER_SIZE + 1];

	read_size = read(fd, buff, BUFFER_SIZE);
	buff[read_size] = 0;
	while (-1 < read_size)
	{
		offset = -1;
		replace(src, ft_strjoin(*src, buff));
		while ((*src)[++offset] || !read_size)
		{
			if ((!read_size && !(*src)[offset]) || (*src)[offset] == '\n')
			{
				if (!make_line(line, *src, offset))
					return (-1);
				if (read_size == 0)
					replace(src, NULL);
				return (0 < read_size);
			}
		}
		read_size = read(fd, buff, BUFFER_SIZE);
		buff[read_size] = 0;
	}
	return (-1);
}

int	ft_get_next_line(int fd, char **line)
{
	static char	*back_up[OPEN_MAX];
	char		buff[BUFFER_SIZE + 1];
	int			check_exist;

	if (!line || read(fd, buff, 0) || BUFFER_SIZE < 1)
		return (-1);
	if (!back_up[fd])
		back_up[fd] = ft_strdup("");
	check_exist = read_exist(line, back_up[fd]);
	if (check_exist)
		return (check_exist);
	return (read_new(line, &(back_up[fd]), fd));
}
