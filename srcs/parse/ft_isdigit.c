/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sham <sham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:25:50 by kimtaeseon        #+#    #+#             */
/*   Updated: 2022/03/17 15:59:20 by sham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}
