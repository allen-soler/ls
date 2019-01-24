/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 13:41:25 by jallen            #+#    #+#             */
/*   Updated: 2019/01/24 17:25:02 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int	check_errors(char *path, int ret, int test)
{
	DIR		*d;
	int		i;
	char	*rights;

	i = 0;
	rights = NULL;
	if (ret == 0 && test == 0)
		i = 1;
	if (!(d = opendir(path)))
	{
		if (i == 0 && test == 1)
			ft_fprintf(2, "ls : %s: %s\n", path, strerror(errno));
		return (i);
	}
	else
		i = 2;
	rights = g_rights(f_stat, rights, path);
	if (rights[0] == 'l' && path[ft_strlen(path) - 1] != '/' && g_flag & L)
		i = 1;
	else if ((g_flag & L) == 0)
		i = 2;
	free(rights);
	closedir(d);
	return (i);
}

void		check_args(char **av, int ac, int start, t_lst **paths)
{
	int		ret;
	t_lst	*files;
	time_t	time;

	ft_sortav(ac, av, start);
	while (start < ac)
	{
		time = 0;
		ret = lstat(av[start], &f_stat);
		(f_stat.st_mode > time) ? time = f_stat.st_mtime : 0;
		if (check_errors(av[start], ret, 0) == 1)
			lst_add(&files, new_node(av[start], (long)time));
		else if (check_errors(av[start], ret, 1) == 2)
			lst_add(paths, new_node(av[start], (long)time));
		start++;
	}
	sorting(paths, &files);
	if (files)
		printing_files(files, *paths);
}

static void	files_space(t_lst *path)
{
	while (path)
	{
		stat(path->content, &f_stat);
		spaces_file(path->content);
		path = path->next;
	}
}

void		printing_files(t_lst *path, t_lst *folders)
{
	char	*tmp;
	char	buf[1000];

	ft_bzero(buf, 1000);
	tmp = NULL;
	init();
	if ((g_flag & L) == 0)
	{
		print_columns(path, "");
		free_list(path);
		folders != NULL ? ft_putchar('\n') : exit(0);
	}
	else if (g_flag & L)
	{
		files_space(path);
		while (path)
		{
			lstat(path->content, &f_stat);
			readlink(path->content, buf, 1000);
			ft_ls_l(path->content, buf, tmp);
			free_node(path);
			path = path->next;
		}
		folders != NULL ? ft_putchar('\n') : exit(0);
	}
}
