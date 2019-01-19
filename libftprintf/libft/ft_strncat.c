/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:34:38 by jallen            #+#    #+#             */
/*   Updated: 2018/11/09 15:54:58 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncat(char *restrict s1, const char *restrict s2, size_t n)
{
	size_t	i;
	size_t	des_len;

	i = 0;
	des_len = ft_strlen(s1);
	while (i < n && s2[i])
	{
		s1[i + des_len] = s2[i];
		i++;
	}
	s1[i + des_len] = '\0';
	return (s1);
}
