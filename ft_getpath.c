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
		swap(start, min);
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
		swap(start, min);
		start = start->next;
	}
}

void	add_path(char *path, t_lst *head, int n, int i)
{
	t_lst			*d_path;
	t_lst			*current;
	DIR				*d;
	struct dirent	*sd;

	d_path = NULL;
	if (!(d = opendir(path)))
		return;
	current = add_child(head, path, i);
	while ((sd = readdir(d)) != NULL)
	{
		sort_ascii(current->child);
		if (sd->d_name[0] != '.')
			lst_add(&current->child, new_node(sd->d_name, 0));	
		if (sd->d_type == DT_DIR && sd->d_name[0] != '.' && n == 0)
			lst_add(&d_path, new_node(check_path(sd->d_name, path, 0), i++));
	}
	sort_ascii(d_path);
	while (d_path)
	{
		add_path(d_path->content, head, 0, ++i);
		d_path = d_path->next;
	}
	closedir(d);
}
