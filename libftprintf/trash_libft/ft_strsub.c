/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:51:49 by nalonso           #+#    #+#             */
/*   Updated: 2018/11/14 10:49:39 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t n)
{
	char *ret;
	char *ptr;

	ret = (char *)malloc(sizeof(char) * n + 1);
	ptr = ret;
	if (!ret || !s)
		return (NULL);
	s += start;
	while (n--)
		*ret++ = *s++;
	*ret = '\0';
	return (ptr);
}
