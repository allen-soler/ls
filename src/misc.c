/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 15:17:57 by jallen            #+#    #+#             */
/*   Updated: 2019/01/22 19:56:57 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int	check_errors(char *path, int ret, int test)
{
	DIR		*d;
	int		i;

	i = 0;
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
	closedir(d);
	return (i);
}

void		check_args(char **av, int ac, int *start, t_lst **paths)
{
	int		ret;
	t_lst	*folders;
	time_t	time;

	ft_sortav(ac, av, *start);
	while (*start < ac)
	{
		time = 0;
		ret = lstat(av[*start], &f_stat);
		(f_stat.st_mode > time) ? time = f_stat.st_mtime : 0;
		if (check_errors(av[*start], ret, 0) == 1)
			lst_add(paths, new_node(av[*start], (long)time));
		else if (check_errors(av[*start], ret, 1) == 2)
			lst_add(&folders, new_node(av[*start], (long)time));
		*start = *start + 1;
	}
	sorting(&folders, paths);
	*start = 0;
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

int			counting_spaces(int spaces, int max, int len)
{
	int		i;

	i = 0;
	if (len == 0)
	{
		while (max > 0)
		{
			i++;
			max /= 10;
		}
		if (i > spaces)
			return (i);
		return (spaces);
	}
	else if (len == 1)
	{
		if (max > spaces)
			return (max);
		return (spaces);
	}
	return (0);
}

void		ft_putnchar(char c, int max, int min, int len)
{
	int	i;

	i = 0;
	if (len == 0)
	{
		while (min > 0)
		{
			i++;
			min /= 10;
		}
		max = max - i;
	}
	else if (len == 1)
		max = max - min + 1;
	while (max > 0)
	{
		write(1, &c, 1);
		max--;
	}
}
