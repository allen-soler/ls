/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:42:51 by jallen            #+#    #+#             */
/*   Updated: 2018/11/09 15:54:25 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t size)
{
	int	i;
	int	len_dest;
	int	len_src;

	i = 0;
	len_dest = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (size < (size_t)len_dest)
		return (size + (size_t)len_src);
	while ((size_t)i < size - (size_t)len_dest - 1 &&
			size >= (size_t)len_dest + 1)
	{
		dst[i + len_dest] = src[i];
		i++;
	}
	dst[i + len_dest] = '\0';
	return ((size_t)len_dest + (size_t)len_src);
}
