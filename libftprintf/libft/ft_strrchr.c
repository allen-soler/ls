/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:40:08 by jallen            #+#    #+#             */
/*   Updated: 2018/11/09 18:31:19 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *str, int c)
{
	size_t	i;
	size_t	hold;

	i = 0;
	hold = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			hold = i;
		i++;
	}
	if (str[hold] == c)
		return ((char *)&str[hold]);
	if (str[i] == c)
		return ((char *)str + i);
	return (0);
}
