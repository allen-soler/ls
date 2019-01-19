/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 11:33:27 by jallen            #+#    #+#             */
/*   Updated: 2018/11/15 12:10:44 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strnew(size_t size)
{
	char		*dest;
	size_t		i;

	i = 0;
	if (!(dest = malloc(sizeof(char) * (size + 1))))
		return (0);
	while (i <= size)
	{
		dest[i] = 0;
		i++;
	}
	return (dest);
}
