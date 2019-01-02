#include "ft_ls.h"

void	ft_print(t_lst *root)
{
	t_lst	*current;
	
	current = root->child;
	while (current)
	{
		printf("%s\n", current->content);
		while (current->child)
		{
			printf("%s\n", current->child->content);
			current->child = current->child->next;
		}
		printf("\n");
		current = current->next;
	}
}

t_lst	*new_node(char *name, int data)
{
	t_lst *new_node;

	if (!(new_node = malloc(sizeof(t_lst))))
		return (0);
	new_node->content = name;
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
