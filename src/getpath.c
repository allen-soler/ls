/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 22:19:00 by jallen            #+#    #+#             */
/*   Updated: 2019/01/13 18:26:18 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	sorting(t_lst *current, t_lst **d_path)
{
	if (current)
	{
		sort_ascii(current->child);
		sort_int(current->child);
		reverse_child(&current->child);
	}
	if (d_path)
	{
		sort_ascii(*d_path);
		sort_int(*d_path);
		reverse_child(d_path);
	}
}

static void	adding_name(char *d_name, t_lst *current, int n, time_t *latest)
{
	char	*tmp;

	*latest = 0;
	tmp = ft_strjoin(current->content, d_name);
	stat(tmp, &f_stat);
	if (f_stat.st_mode > *latest)
		*latest = f_stat.st_mtime;
	if (d_name[0] != '.' && n == 0)
		lst_add(&current->child, new_node(d_name, (int)latest));
	if (n == 1)
		lst_add(&current->child, new_node(d_name, (int)latest));
	free(tmp);
}

void		add_path(char *path, t_lst *head, int n, int i)
{
	DIR				*d;
	t_lst			*current;
	t_lst			*d_path;
	time_t			lst;

	d_path = NULL;
	if (!(d = opendir(path)))
		return ;
	current = add_child(head, path, i);
	while ((sd = readdir(d)) != NULL)
	{
		adding_name(sd->d_name, current, n, &lst);
		if (sd->d_type == DT_DIR && sd->d_name[0] != '.' && n == 0)
			lst_add(&d_path, new_node(check_path(sd->d_name, path, 0), lst));
	}
	sorting(current, &d_path);
	while (d_path)
	{
		add_path(d_path->content, head, 0, ++i);
		d_path = d_path->next;
	}
	closedir(d);
}
