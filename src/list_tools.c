/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:29:17 by jallen            #+#    #+#             */
/*   Updated: 2019/01/15 16:02:00 by jallen           ###   ########.fr       */
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
	new_node->child = NULL;
	return (new_node);
}

t_lst	*add_sibling(t_lst *n, char *name, int data)
{
	if (n == NULL)
		return (NULL);
	while (n->next)
		n = n->next;
	return (n->next = new_node(name, data));
}

t_lst	*add_child(t_lst *n, char *name, int data)
{
	if (n == NULL)
		return (NULL);
	if (n->child)
		return (add_sibling(n->child, name, data));
	else
		return (n->child = new_node(name, data));
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
