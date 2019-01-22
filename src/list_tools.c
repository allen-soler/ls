/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:29:17 by jallen            #+#    #+#             */
/*   Updated: 2019/01/22 20:38:57 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_lst	*new_node(char *name, int data)
{
	t_lst	*new_node;

	new_node = NULL;
	if (!(new_node = malloc(sizeof(t_lst))))
		return (0);
	if (name == NULL)
		new_node->content = NULL;
	else
		new_node->content = ft_strdup(name);
	new_node->data = data;
	new_node->next = NULL;
	return (new_node);
}

void	lst_add(t_lst **head, t_lst *new)
{
	t_lst	*tmp;

	if (*head)
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*head = new;
}

void	free_list(t_lst *head)
{
	t_lst	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->content);
		free(tmp);
	}
}

void	free_node(t_lst *head)
{
	free(head->content);
	free(head);
}

void	nchar(int space, char c)
{
	while (space > 0)
	{
		write(1, &c, 1);
		space--;
	}
}
