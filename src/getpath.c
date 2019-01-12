/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 22:19:00 by jallen            #+#    #+#             */
/*   Updated: 2019/01/12 19:10:22 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	sorting(t_lst *current, t_lst *d_path)
{
	if (current != NULL)
		sort_ascii(current);
	if (d_path != NULL)
		sort_ascii(d_path);
}

static void	recursive_path(t_lst *head, char *path, int n)
{
	DIR		*d;
	t_lst	*current;
	t_lst	*d_path;

	d_path = NULL;
	if (!(d = opendir(path)))
		return ;
	current = add_child(head, path, 0);
	while ((sd = readdir(d)) != NULL)
	{
		if (sd->d_name[0] != '.' && n == 0)
			lst_add(&current->child, new_node(sd->d_name, 0));
		else if (sd->d_name[0] && n == 1)
			lst_add(&current->child, new_node(sd->d_name, 0));
		if (sd->d_type == DT_DIR && sd->d_name[0] != '.')
			lst_add(&d_path, new_node(check_path(sd->d_name, path, 0), 0));
	}
	sorting(current, d_path);
	while (d_path)
	{
		recursive_path(head, d_path->content, n);
		d_path = d_path->next;
	}
	closedir(d);
}

static void	first_path(t_lst *head, t_lst **d_path, int i, int n, char *path)
{
	DIR				*d;
	t_lst			*root;
	t_lst			*current;

	if (!(d = opendir(path)))
		return ;
	root = add_child(head, NULL, 0);
	current = add_child(root, path, i);
	while ((sd = readdir(d)) != NULL)
	{
		if (sd->d_name[0] != '.' && n == 0)
			lst_add(&current->child, new_node(sd->d_name, 0));
		else if (sd->d_name[0] && n == 1)
			lst_add(&current->child, new_node(sd->d_name, 0));
		if (sd->d_type == DT_DIR && sd->d_name[0] != '.' && i == 0)
			lst_add(d_path,
					new_node(check_path(sd->d_name, current->content, 0), i));
	}
	sorting(current, *d_path);
	closedir(d);
}

void		add_path(char *path, t_lst *head, int n, int i)
{
	t_lst			*root;
	t_lst			*d_path;

	d_path = NULL;
	first_path(head, &d_path, i, n, path);
	while (d_path && i == 0)
	{
		root = add_child(head, NULL, 0);
		recursive_path(root, d_path->content, n);
		d_path = d_path->next;
	}
}
