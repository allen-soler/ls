/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 16:48:42 by nalonso           #+#    #+#             */
/*   Updated: 2019/01/21 16:49:51 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		split_list(t_lst *source, t_lst **front, t_lst **back)
{
	t_lst	*fast;
	t_lst	*slow;

	slow = source;
	fast = source->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front = source;
	*back = slow->next;
	slow->next = NULL;
}

static t_lst	*sort_and_merge(t_lst *a, t_lst *b)
{
	t_lst *result;

	result = NULL;
	if (!a)
		return (b);
	else if (!b)
		return (a);
	if (a->data <= b->data)
	{
		result = a;
		result->next = sort_and_merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sort_and_merge(a, b->next);
	}
	return (result);
}

static t_lst	*sort_and_merge_ascii(t_lst *a, t_lst *b)
{
	t_lst *result;

	result = NULL;
	if (!a)
		return (b);
	else if (!b)
		return (a);
	if (a->data <= b->data && ft_strcmp(a->content, b->content) >= 0)
	{
		result = a;
		result->next = sort_and_merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sort_and_merge(a, b->next);
	}
	return (result);
}

void			merge_sort(t_lst **head_ref, int func)
{
	t_lst *head;
	t_lst *a;
	t_lst *b;

	head = *head_ref;
	if (head == NULL || head->next == NULL)
	{
		return ;
	}
	split_list(head, &a, &b);
	merge_sort(&a, func);
	merge_sort(&b, func);
	if (func == 0)
		*head_ref = sort_and_merge(a, b);
	else if (func == 1)
		*head_ref = sort_and_merge_ascii(a, b);
}
