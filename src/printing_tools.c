/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 13:59:09 by jallen            #+#    #+#             */
/*   Updated: 2019/01/23 14:01:11 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		num_len(int nb)
{
	int i;

	i = 0;
	while (nb != 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

void	nchar(int space, char c)
{
	while (space > 0)
	{
		write(1, &c, 1);
		space--;
	}
}

int		counting_spaces(int spaces, int max, int len)
{
	int		i;

	i = 0;
	if (len == 0)
	{
		while (max > 0)
		{
			i++;
			max /= 10;
		}
		if (i > spaces)
			return (i);
		return (spaces);
	}
	else if (len == 1)
	{
		if (max > spaces)
			return (max);
		return (spaces);
	}
	return (0);
}

int		n_sp(int max, int min, int len)
{
	int	i;

	i = 0;
	if (len == 0)
	{
		while (min > 0)
		{
			i++;
			min /= 10;
		}
		max = max - i;
	}
	else if (len == 1)
		max = max - min + 1;
	return (max);
}
