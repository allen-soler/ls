/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 11:22:36 by jallen            #+#    #+#             */
/*   Updated: 2018/11/16 17:02:44 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_lensize(int n)
{
	int		counter;

	counter = 0;
	if (n < 0)
		counter++;
	while (n > 0 || n < 0)
	{
		counter++;
		n = n / 10;
	}
	return (counter);
}

static char		*ft_posn(int n, char *dest)
{
	int		i;
	int		len;

	i = ft_lensize(n) - 1;
	len = ft_lensize(n);
	while (n > 0)
	{
		dest[i] = n % 10 + 48;
		n /= 10;
		i--;
	}
	dest[len] = '\0';
	return (dest);
}

static char		*ft_negn(int n, char *dest)
{
	int		i;
	int		len;

	i = ft_lensize(n) - 1;
	len = ft_lensize(n);
	dest[0] = '-';
	while (n < 0)
	{
		dest[i] = -(n % 10) + 48;
		n /= 10;
		i--;
	}
	dest[len] = '\0';
	return (dest);
}

char			*ft_itoa(int n)
{
	char	*dest;

	if (!(dest = malloc(sizeof(char) * (ft_lensize(n) + 1))))
		return (0);
	if (n == 0)
	{
		if (!(dest = malloc(sizeof(char) * 2)))
			return (0);
		dest[0] = '0';
		dest[1] = '\0';
	}
	if (n > 0)
	{
		ft_posn(n, dest);
		return (dest);
	}
	if (n < 0)
	{
		ft_negn(n, dest);
		return (dest);
	}
	return (dest);
}
