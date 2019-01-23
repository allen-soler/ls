/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 15:17:57 by jallen            #+#    #+#             */
/*   Updated: 2019/01/23 18:32:31 by jallen           ###   ########.fr       */
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
			ft_fprintf(2, "ls : %s %s\n", path, strerror(errno));
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
	t_lst	*folders;
	time_t	time;

	ft_sortav(ac, av, start);
	while (start < ac)
	{
		time = 0;
		ret = lstat(av[start], &f_stat);
		(f_stat.st_mode > time) ? time = f_stat.st_mtime : 0;
		if (check_errors(av[start], ret, 0) == 1)
			lst_add(paths, new_node(av[start], (long)time));
		else if (check_errors(av[start], ret, 1) == 2)
			lst_add(&folders, new_node(av[start], (long)time));
		start++;
	}
	sorting(&folders, paths);
	while (folders)
	{
		lst_add(paths, new_node(folders->content, 1));
		free_node(folders);
		folders = folders->next;
	}
}

void		printing_files(char *file, t_lst *path)
{
	char	*tmp;
	char	buf[1000];

	if ((g_flag & L) == 0)
	{
		ft_printf("%s ", file);
		if (path == NULL || path->data == 1)
			ft_putchar('\n');
	}
	else if (g_flag & L)
	{
		lstat(file, &f_stat);
		readlink(tmp, buf, 1000);
		ft_ls_l(file, buf, file);
	}
}

void		ft_normal_ls(t_lst *current, char *path)
{
	char	*rights;
	char	*tmp;
	char	buf[1000];
	int		i;

	rights = NULL;
	ft_bzero(buf, 1000);
	while (current)
	{
		i = n_sp(g_space.name, ft_strlen(current->content), 1);
		tmp = ft_strjoin(path, current->content);
		lstat(tmp, &f_stat);
		rights = g_rights(f_stat, rights, tmp);
		ls_colors(current->content, buf, rights, 0);
		ft_putchar('\n');
		current = current->next;
		free(rights);
		free(tmp);
	}
}
