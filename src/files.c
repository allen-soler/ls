/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 15:17:57 by jallen            #+#    #+#             */
/*   Updated: 2019/01/24 13:20:34 by jallen           ###   ########.fr       */
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
	printing_files(files, *paths);		
}

void		spaces_file(char *name)
{
	grp = getgrgid(f_stat.st_gid);
	g_space.one = counting_spaces(g_space.one, (int)f_stat.st_size, 0);
	g_space.two = counting_spaces(g_space.two, (int)f_stat.st_nlink, 0);
	g_space.name = counting_spaces(g_space.name, ft_strlen(name), 1);
	if ((pwd = getpwuid(f_stat.st_uid)) != NULL)
		g_space.user = counting_spaces(g_space.user,\
				ft_strlen(pwd->pw_name), 1);
	g_space.group = counting_spaces(g_space.group,\
			ft_strlen(grp->gr_name), 1);

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

	g_space.one = 0;
	g_space.two = 0;
	g_space.name = 0;
	g_space.group = 0;
	g_space.user = 0;
	ft_bzero(buf, 1000);
	tmp = NULL;
	if ((g_flag & L) == 0)
	{
		if (folders == NULL || folders->data == 1)
			ft_putchar('\n');
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
		if (folders)
			ft_putchar('\n');
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
