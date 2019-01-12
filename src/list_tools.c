/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:29:17 by jallen            #+#    #+#             */
/*   Updated: 2019/01/12 16:57:26 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ft_print(t_lst *current)
{

	while (current)
	{
		ft_printf("first->child = %s %i\n", current->content, current->data);
		while (current->child)
		{
			ft_printf("second->child = %s %i\n", current->child->content, current->child->data);
			while (current->child->child)
			{
				ft_printf("third->child = %s\n", current->child->child->content);
				current->child->child = current->child->child->next;
			}
			current->child = current->child->next;
		}
		ft_printf("\n\n");
		current = current->next;
	}
}

t_lst	*new_node(char *name, int data)
{
	t_lst	*new_node;

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
void	test(t_lst *head)
{
	t_lst	*current = NULL;
	t_lst	*current1 = NULL;
	t_lst	*current2 = NULL;
	t_lst	*current3 = NULL;
	t_lst	*current4 = NULL;
	current = add_child(head, "head current", 1);
	current1 = add_child(current, "first", 1);
	for (int i = 0; i < 5; i++)
		lst_add(&current1->child, new_node("current second", i));
	
	current2 = add_child(current, "second", 2);
	for (int i = 0; i < 5; i++)
		lst_add(&current2->child, new_node("current1 third", i));
	
	current3 = add_child(head, "head current", 1);
	current4 = add_child(current3, "first", 1);
	for (int i = 0; i < 5; i++)
		lst_add(&current4->child, new_node("current second", i));

}

int	main(int ac, char **av)
{
	t_lst	*head = NULL;
	t_lst	*current = NULL;
	head = new_node(NULL, 0);
	test(head);
	current = head->child;
	while (current)
	{
		ft_printf("%s\n", current->content);
		while (current->child)
		{
			ft_printf("%s\n", current->child->content);
			while (current->child->child)
			{
				ft_printf("%s\n", current->child->child->content);
				current->child->child = current->child->child->next;
			}
			ft_printf("\n");
			current->child = current->child->next;
		}
		current = current->next;
	}
}
