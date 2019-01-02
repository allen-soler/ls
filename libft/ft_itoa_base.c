/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 19:17:58 by jallen            #+#    #+#             */
/*   Updated: 2018/11/17 19:32:00 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_mcounter(int val, int base)
{
	int		i;

	i = 0;
	if (base == 0)
		return (0);
	while (val > 0 || val < 0)
	{
		val /= base;
		i++;
	}
	return (i);
}

static char		*ft_positive_base(int val, int base, char *dest)
{
	int		i;
	int		m_size;
	char	*c_base;

	c_base = ft_strdup("0123456789ABCDF");
	m_size = ft_mcounter(val, base);
	i = m_size - 1;
	if (!(dest = malloc(sizeof(char) * (m_size + 1))))
		return (0);
	while (val > 0 && i >= 0)
	{
		dest[i] = c_base[val % base];
		val /= base;
		i--;
	}
	dest[m_size] = '\0';
	return (dest);
}

static char		*ft_neg_base(int val, int base, char *dest)
{
	int		i;
	int		m_size;
	char	*c_base;

	c_base = ft_strdup("0123456789ABCDF");
	m_size = ft_mcounter(val, base);
	i = m_size;
	if (!(dest = malloc(sizeof(char) * (m_size + 2))))
		return (0);
	dest[0] = '-';
	while (val < 0 && i >= 1)
	{
		dest[i] = c_base[-(val % base)];
		val /= base;
		i--;
	}
	dest[m_size + 1] = '\0';
	return (dest);
}

char			*ft_itoa_base(int val, int base)
{
	char	*dest;

	dest = 0;
	if (val == 0)
	{
		if (!(dest = malloc(sizeof(char) * 2)))
			return (0);
		dest[0] = 48;
		dest[1] = '\0';
		return (dest);
	}
	else if (val > 0 && base <= 16)
	{
		dest = ft_positive_base(val, base, dest);
		return (dest);
	}
	else if (val < 0 && base == 10)
	{
		dest = ft_neg_base(val, base, dest);
		return (dest);
	}
	return (0);
}
