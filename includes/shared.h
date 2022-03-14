/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 00:30:44 by pac-man           #+#    #+#             */
/*   Updated: 2022/03/14 21:13:00 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <time.h>
# include "env.h"

// libft
int			ft_isdigit(char c);
int			ft_strlen(const char *s);
void		*ft_memset(void *b, int c, int len);
void		*ft_calloc(size_t count, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strdup(char *s);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_get_next_line(int fd, char **line);
char		*ft_itoa(int n);
int	        ft_atoi(const char *str);
int         ft_cmpstr(char *str1, char *str2);

// ts added
int			file_open(char *path);
int			ft_get_next_line(int fd, char **line);
void		*replace(char **out, char *src);
char		*ft_strdup(char *s);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
int			ft_strlen(const char *s);
char		**ft_split(char const *s, char c);

#endif
