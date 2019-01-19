/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:40:02 by jallen            #+#    #+#             */
/*   Updated: 2018/11/16 17:24:25 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_len_s(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i] == '\t' || s[i] == ' ' || s[i] == '\n')
		i++;
	return (i);
}

static int		ft_len_e(char const *s)
{
	size_t	i;

	i = ft_strlen(s) - 1;
	while (s[i] == '\t' || s[i] == ' ' || s[i] == '\n')
		i--;
	i++;
	return (i);
}

char			*ft_strtrim(char const *s)
{
	char	*dest;
	size_t	i;
	size_t	len;

	i = 0;
	if (!s)
		return (0);
	len = ft_len_e(s) - ft_len_s(s);
	if (ft_len_e(s) == 0)
	{
		if (!(dest = malloc(sizeof(char) * 2)))
			return (0);
		dest[0] = 0;
		dest[1] = '\0';
		return (dest);
	}
	if (!(dest = malloc(sizeof(char) * (len + 1))))
		return (0);
	while (i < len)
	{
		dest[i] = s[ft_len_s(s) + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
