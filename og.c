#include "ft_ls.h"

void	ft_print(t_lst *root)
{
	while (root)
	{
		while (root->child)
		{
			printf("child = %s\n", root->child->content);
			printf("-----------------------------\n");
			while (root->child->child)
			{
				printf("node->child->child %s\n", root->child->child->content);
				root->child->child = root->child->child->next;
			}
			printf("\n");
			root->child = root->child->next;
		}
		root = root->next;
	}
}

t_lst	*test(t_lst *root)
{
	int i = 0;
	t_lst *first_child = add_child(root, "first-child", 0);
	for (int i = 0; i < 4; i++)
		lst_add(&first_child->child, new_node("inside first child child", i));
	return (first_child);
}
int	main(int ac, char **av)
{
	t_lst *root;
	root = NULL;
	root = new_node(0,0);
	t_lst *first_child = add_child(root, "first-child", 0);
	for (int i = 0; i < 4; i++)
		lst_add(&first_child->child, new_node("inside first child child", i));
	t_lst *second_child = add_child(root, "second-child", 0);
for (int i = 0; i < 4; i++)
    lst_add(&second_child->child, new_node("inside second child child", i));
	ft_print(root);
	return (0);
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


