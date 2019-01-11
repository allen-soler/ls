/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 12:08:38 by jallen            #+#    #+#             */
/*   Updated: 2018/11/15 12:20:49 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char		*dest;
	size_t		i;

	i = 0;
	if (!(dest = malloc(size)))
		return (0);
	while (i < size)
	{
		dest[i] = 0;
		i++;
	}
	return (dest);
}
