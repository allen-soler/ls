/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 22:19:00 by jallen            #+#    #+#             */
/*   Updated: 2019/01/13 23:22:11 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	sorting(t_lst *current, t_lst **d_path, char *flags)
{
	if (current)
	{
		sort_ascii(current->child);
		if (flags[3] == '4')
			sort_int(current->child);
		if (flags[4] == '5')
			reverse_child(&current->child);
	}
	if (d_path)
	{
		sort_ascii(*d_path);
		if (flags[3] == '4')
			sort_int(*d_path);
		if (flags[4] == '5')
			reverse_child(d_path);
	}
}

static void	adding_name(char *d_name, t_lst *current, char *flags,
		time_t *latest)
{
	char	*tmp;
	time_t	test;

	test = 0;
	tmp = ft_strjoin(current->content, d_name);
	lstat(tmp, &f_stat);
	if (f_stat.st_mode > test)
		test = f_stat.st_mtime;
	*latest = test;
	if (d_name[0] != '.' && flags[1] == '0')
		lst_add(&current->child, new_node(d_name, (long)test));
	if (flags[1] == '2')
		lst_add(&current->child, new_node(d_name, (long)test));
	free(tmp);
}

static int	check_a(char *flags, char *d_name)
{
	if (flags[1] == '2' && flags[2] == '3' &&
			ft_strcmp(d_name, ".") != 0 && ft_strcmp(d_name, "..") != 0)
		return (1);
	return (0);
}

void		add_path(char *path, t_lst *head, char *flags)
{
	DIR				*d;
	t_lst			*current;
	t_lst			*d_path;
	time_t			lst;

	d_path = NULL;
	if (!(d = opendir(path)))
		return ;
	current = add_child(head, path, 0);
	while ((sd = readdir(d)) != NULL)
	{
		adding_name(sd->d_name, current, flags, &lst);
		if (sd->d_type == DT_DIR && sd->d_name[0] != '.' && flags[2] == '3')
			lst_add(&d_path, new_node(check_p(sd->d_name, path, 0), (long)lst));
		if (sd->d_type == DT_DIR && check_a(flags, sd->d_name) == 1)
			lst_add(&d_path, new_node(check_p(sd->d_name, path, 0), (long)lst));
	}
	sorting(current, &d_path, flags);
	while (d_path != NULL)
	{
		add_path(d_path->content, head, flags);
		d_path = d_path->next;
	}
	closedir(d);
}
