/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 15:17:57 by jallen            #+#    #+#             */
/*   Updated: 2019/01/19 15:42:28 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		counting_spaces(int spaces, int max)
{
	if (max > spaces)
		return (max);
	return (spaces);	
}

void	ft_putnchar(char c, int max, int min)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (max > 0)
	{
		i++;
		max /= 10;
	}
	while (min > 0)
	{
		j++;
		min /= 10;
	}
	i = i - j;
	while (i > 0)
	{
		write(1, &c, 1);
		i--;
	}	
}
