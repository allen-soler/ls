/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:23:29 by jallen            #+#    #+#             */
/*   Updated: 2018/11/09 15:53:59 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *restrict s1, const char *restrict s2)
{
	int	i;
	int	len_des;
	int	len_src;

	i = 0;
	len_des = ft_strlen(s1);
	len_src = ft_strlen(s2);
	if (len_src == 0)
		return (s1);
	while (s2[i] != '\0')
	{
		s1[i + len_des] = s2[i];
		i++;
	}
	s1[i + len_des] = '\0';
	return (s1);
}
