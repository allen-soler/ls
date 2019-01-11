/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:28:10 by jallen            #+#    #+#             */
/*   Updated: 2019/01/11 16:46:05 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	swap_list(t_lst *p1, t_lst *p2)
{
	char	*tmp;
	int		i;

	i = p1->data;
	p1->data = p2->data;
	p2->data = i;
	tmp = p1->content;
	p1->content = p2->content;
	p2->content = tmp;
}

void	sort_int(t_lst *head)
{
	t_lst	*start;
	t_lst	*traverse;
	t_lst	*min;

	start = head;
	if (head == NULL)
		return ;
	while (start->next)
	{
		min = start;
		traverse = start->next;
		while (traverse)
		{
			if (min->data > traverse->data)
				min = traverse;
			traverse = traverse->next;
		}
		swap_list(start, min);
		start = start->next;
	}
}

void	sort_ascii(t_lst *head)
{
	t_lst	*start;
	t_lst	*traverse;
	t_lst	*min;

	start = head;
	if (head == NULL)
		return ;
	while (start->next)
	{
		min = start;
		traverse = start->next;
		while (traverse)
		{
			if (ft_strcmp(min->content, traverse->content) > 0)
				min = traverse;
			traverse = traverse->next;
		}
		swap_list(start, min);
		start = start->next;
	}
}
