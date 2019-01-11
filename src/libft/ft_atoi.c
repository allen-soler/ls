/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:50:08 by jallen            #+#    #+#             */
/*   Updated: 2018/11/09 16:42:48 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	int		i;
	long	hold;
	int		neg;

	i = 0;
	hold = 0;
	neg = 0;
	while (str[i] >= 0 && str[i] <= 32 && str[i] != 27)
		i++;
	if (str[i] == '-' && str[i + 1] >= 48)
	{
		neg++;
		i++;
	}
	if (str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (hold > hold * 10 + str[i] - 48)
			return (neg == 1 ? 0 : -1);
		hold = hold * 10 + str[i] - 48;
		i++;
	}
	return (neg == 1 ? -((int)hold) : (int)hold);
}
