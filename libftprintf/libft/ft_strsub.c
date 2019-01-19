/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 14:24:14 by jallen            #+#    #+#             */
/*   Updated: 2018/11/15 15:11:08 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (!(dest = malloc(sizeof(char) * (len + 1))))
		return (0);
	while (s[start] != '\0' && i < len)
	{
		dest[i] = s[(size_t)start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
