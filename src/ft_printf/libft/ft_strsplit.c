/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:51:43 by nalonso           #+#    #+#             */
/*   Updated: 2018/11/14 10:46:58 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int		word_count(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s)
	{
		if (*s != c)
			len++;
		while (*s != c && *(s + 1))
			s++;
		s++;
	}
	return (len);
}

static int		word_length(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s == c)
		s++;
	while (*s++ != c)
		len++;
	return (++len);
}

static char		*sp_strdup(char const *s, char c)
{
	char	*ret;
	char	*ptr;

	if (!(ret = (char *)malloc(sizeof(char) * (word_length(s, c) + 1))))
		return (NULL);
	ptr = ret;
	while (*s != c && *s)
		*ret++ = *s++;
	*ret = '\0';
	return (ptr);
}

static void		*free_tab(char **tab)
{
	while (*tab)
		free(*tab++);
	free(tab);
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		nb_word;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	nb_word = word_count(s, c);
	tab = (char **)malloc(sizeof(char *) * (nb_word + 1));
	if (!tab)
		return (NULL);
	while (i < nb_word)
	{
		while (*s == c)
			s++;
		if (!(tab[i] = sp_strdup(s, c)))
			return (free_tab(tab));
		while (*s != c && *s)
			s++;
		i++;
	}
	tab[nb_word] = NULL;
	return (tab);
}
