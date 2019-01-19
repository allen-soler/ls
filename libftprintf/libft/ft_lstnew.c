/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 19:30:44 by jallen            #+#    #+#             */
/*   Updated: 2018/11/17 14:48:11 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*cnt;

	if (!(cnt = malloc(sizeof(t_list))))
		return (0);
	cnt->next = 0;
	if (content != NULL)
	{
		if (!(cnt->content = malloc(content_size)))
			return (0);
		ft_memcpy(cnt->content, content, content_size);
		cnt->content_size = content_size;
	}
	else
	{
		cnt->content = 0;
		cnt->content_size = 0;
	}
	return (cnt);
}
