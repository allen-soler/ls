/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 22:19:00 by jallen            #+#    #+#             */
/*   Updated: 2019/01/19 16:48:36 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	sorting(t_lst **current, t_lst **d_path)
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

static int	adding_n(int i)
{
	if (i == 0)
	{
		if (flag & A)
			return (1);
		else if ((flag & A) == 0 && sd->d_name[0] != '.')
			return (2);
	}
	else if (i == 1)
	{
		if (flag & A && flag & R && ft_strcmp(sd->d_name, ".") != 0 &&
				ft_strcmp(sd->d_name, "..") != 0)
			return (1);
		else if ((flag & A) == 0 && sd->d_name[0] != '.' && flag & R)
			return (2);
	}
	return (0);
}

static void	adding_path(t_lst **d_path, t_lst **head, char *path, int *i)
{
	char	*tmp;
	time_t	time;

	time = 0;
	tmp = check_p(sd->d_name, path, 0);
	if (f_stat.st_mode > time)
		time = f_stat.st_mtime;
	if (sd->d_name[0] != '.')
		*i = *i + f_stat.st_blocks;
	if (adding_n(0))
	{
		lst_add(head, new_node(sd->d_name, (long)time));
		space.one = counting_spaces(space.one, f_stat.st_size);
		space.two = counting_spaces(space.two, f_stat.st_nlink);
	}
	if (sd->d_type == DT_DIR && adding_n(1))
		lst_add(d_path, new_node(tmp, (long)time));
	free(tmp);
}

static void	adding_list(DIR *d, char *path, t_lst **d_path)
{
	char	*tmp;
	t_lst	*head;
	int		i;

	i = 0;
	head = NULL;
	space.one = 0;
	space.two = 0;
	while ((sd = readdir(d)) != NULL)
	{
		tmp = ft_strjoin(path, sd->d_name);
		lstat(tmp, &f_stat);
		adding_path(d_path, &head, path, &i);
		free(tmp);
	}
	sorting(&head, d_path);
	ft_print_ls(head, path, i);
	free_list(head);
}

void		add_path(t_lst *d_path, char *path, int i)
{
	char	*tmp;
	DIR		*d;

	d_path = NULL;
	tmp = check_p(path, "", 1);
	if (i > 0)
		ft_putendl(tmp);
	if (!(d = opendir(path)))
	{
		ft_fprintf(2, "ls: %s %s\n", tmp, strerror(errno));
		free(tmp);
		return ;
	}
	free(tmp);
	adding_list(d, path, &d_path);
	while (d_path)
	{
		ft_putchar('\n');
		add_path(d_path, d_path->content, 1);
		free(d_path->content);
		free(d_path);
		d_path = d_path->next;
	}
	closedir(d);
}
