/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 09:36:57 by jallen            #+#    #+#             */
/*   Updated: 2018/11/16 19:03:23 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_countm(char const *str, char split)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	if (str[i] && str[i] != split)
		counter++;
	while (str[i] != '\0')
	{
		if (str[i - 1] == split && str[i] != split)
			counter++;
		i++;
	}
	return (counter);
}

static char		*ft_add(char const *str, char split, char *dest)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j] != '\0' && str[j] != split)
		j++;
	if (!(dest = malloc(sizeof(char) * (j + 1))))
		return (0);
	while (str[i] != '\0' && str[i] != split)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char		**ft_addwords(char const *str, char split, char **dest)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	if (str[i] != split)
	{
		dest[counter] = ft_add(&str[i], split, dest[counter]);
		counter++;
	}
	while (str[i] != '\0')
	{
		if (str[i - 1] == split && str[i] != split)
		{
			dest[counter] = ft_add(&str[i], split, dest[counter]);
			counter++;
		}
		i++;
	}
	return (dest);
}

char			**ft_strsplit(char const *str, char split)
{
	char	**dest;
	int		i;

	if (!str)
		return (0);
	i = ft_countm(str, split);
	if (!(dest = malloc(sizeof(char *) * (i + 1))))
		return (0);
	ft_addwords(str, split, dest);
	dest[i] = 0;
	return (dest);
}
