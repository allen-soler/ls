/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:51:25 by jallen            #+#    #+#             */
/*   Updated: 2018/11/09 15:52:59 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *str, const char *find)
{
	int	i;
	int	j;

	i = 0;
	if (find[i] == '\0')
		return ((char *)str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] == find[j] && find[j] != '\0')
			j++;
		if (!find[j])
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}
