/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 22:19:00 by jallen            #+#    #+#             */
/*   Updated: 2019/01/13 16:54:09 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	sorting(t_lst *current, t_lst **d_path)
{
	if (current != NULL)
		sort_ascii(current);
	if (current != NULL)
		reverse_child(&current);
	if (d_path)
	{
		sort_ascii(*d_path);
		reverse_child(d_path);
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
		if (sd->d_name[0] != '.')
			lst_add(&current->child, new_node(sd->d_name, 0));	
		if (sd->d_type == DT_DIR && sd->d_name[0] != '.' && n == 0)
			lst_add(&d_path, new_node(check_path(sd->d_name, path, 0), i++));
	}
	sorting(current, &d_path);
	while (d_path)
	{
		add_path(d_path->content, head, 0, ++i);
		d_path = d_path->next;
	}
	closedir(d);
}
