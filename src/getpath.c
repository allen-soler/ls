/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 22:19:00 by jallen            #+#    #+#             */
/*   Updated: 2019/01/17 20:37:23 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	sorting(t_lst **current, t_lst **d_path, f_fl flag)
{
	if (current != NULL)
	{
		if ((flag & T) == 0)
			sort_ascii(*current);
		if (flag & T)
			sort_int(*current);
		if (flag & RR)
			reverse_child(current);
	}
	if (d_path)
	{
		if ((flag & T) < 0)
			sort_ascii(*d_path);
		if (flag & T)
			sort_int(*d_path);
		if (flag & RR)
			reverse_child(d_path);
	}
}

static int	adding_n(char *name, f_fl flag)
{
	if (flag & A)
		return (1);
	else if ((flag & A) == 0 && name[0] != '.')
		return (2);
	return (0);
}

static int	adding_p(char *name, f_fl flag)
{
	if (flag & A && flag & R && ft_strcmp(name, ".") != 0 &&
			ft_strcmp(name, "..") != 0)
		return (1);
	else if ((flag & A) == 0 && name[0] != '.' && flag & R)
		return (2);
	return (0);
}

static void	adding_list(DIR *d, char *path, t_lst **d_path, f_fl flag)
{
	char	*tmp;
	time_t	time;
	t_lst	*head;
	int		i;

	head = NULL;
	while ((sd = readdir(d)) != NULL)
	{
		time = 0;
		tmp = ft_strjoin(path, sd->d_name);
		lstat(tmp, &f_stat);
		if (f_stat.st_mode > time)
			time = f_stat.st_mtime;
		if (sd->d_name[0] != '.')
			i = i + f_stat.st_blocks;
		if (adding_n(sd->d_name, flag))
			lst_add(&head, new_node(sd->d_name, (long)time));
		if (sd->d_type == DT_DIR && adding_p(sd->d_name, flag))
			lst_add(d_path, new_node(check_p(sd->d_name, path, 0), (long)time));
		free(tmp);
	}
	sorting(&head, d_path, flag);
	ft_print_ls(head, path, i);
	free_list(head);
}

void		add_path(char *path, f_fl flag)
{
	t_lst	*d_path;
	DIR		*d;

	d_path = NULL;
	if (!(d = opendir(path)))
	{
		path = check_p(path, "", 1);
		ft_fprintf(2, "ls: %s %s\n", path, strerror(errno));
		free(path);
		return ;
	}
	adding_list(d, path, &d_path, flag);
	while (d_path)
	{
		ft_putchar('\n');
		add_path(d_path->content, flag);
		free(d_path->content);
		d_path = d_path->next;
	}
	closedir(d);
}
