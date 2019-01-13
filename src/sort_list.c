/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:28:10 by jallen            #+#    #+#             */
/*   Updated: 2019/01/13 23:22:42 by jallen           ###   ########.fr       */
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
			if (min->data < traverse->data)
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

void	reverse_child(t_lst **head_ref)
{
	t_lst	*current;
	t_lst	*next;
	t_lst	*prev;

	current = *head_ref;
	next = NULL;
	prev = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head_ref = prev;
}

void	ft_sortav(int ac, char **av, int start)
{
	char	*tmp;
	int		i;

	i = start;
	while (i < ac - 1)
	{
		if (ft_strcmp(av[i], av[i + 1]) > 0)
		{
			tmp = av[i];
			av[i] = av[i + 1];
			av[i + 1] = tmp;
			i = start;
		}
		i++;
	}
}
