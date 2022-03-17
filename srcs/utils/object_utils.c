/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimtaeseon <kimtaeseon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 22:49:58 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/17 17:59:21 by kimtaeseon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "shared.h"
#include "structures.h"

void	ft_exit(int code)
{
	while (1)
		;
	exit(code);
}

void	oadd(t_object **list, t_object *new)
{
	t_object	*cur;

	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	cur = *list;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

t_object	*olast(t_object *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}
