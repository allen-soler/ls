/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 22:19:00 by jallen            #+#    #+#             */
/*   Updated: 2018/12/12 23:18:18 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	swap(t_lst *p1, t_lst *p2)
{
	char	*tmp;

	tmp = p1->content;
	p1->content = p2->content;
	p2->content = tmp;
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
		swap(start, min);
		start = start->next;
	}
}

void	add_path(char *path, t_lst *head, int n, int i)
{
	char			*d_path;
	t_lst			*current;
	DIR				*d;
	struct dirent	*sd;

	d_path = NULL;
	if (!(d = opendir(path)))
		return;
	current = add_child(head, path, i);
	while ((sd = readdir(d)) != NULL)
	{
		if (sd->d_name[0] != '.')
			lst_add(&current->child, new_node(sd->d_name, 0));	
		if (sd->d_type == DT_DIR && sd->d_name[0] != '.' && n == 0)
		{
			d_path = check_path(sd->d_name, path, 0);
			add_path(d_path, head, n, i);
		}
	}
	closedir(d);
}

int	main(int ac, char **av)
{
	t_lst	*root;

	root = NULL;
	root = new_node(NULL,0);
	add_path("./", root, 0, 0);
	ft_print(root);
	return (0);
}