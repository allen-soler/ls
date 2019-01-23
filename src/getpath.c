/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 22:19:00 by jallen            #+#    #+#             */
/*   Updated: 2019/01/23 14:32:22 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		spaces(void)
{
	grp = getgrgid(f_stat.st_gid);
	g_space.one = counting_spaces(g_space.one, (int)f_stat.st_size, 0);
	g_space.two = counting_spaces(g_space.two, (int)f_stat.st_nlink, 0);
	g_space.name = counting_spaces(g_space.name, ft_strlen(sd->d_name), 1);
	if ((pwd = getpwuid(f_stat.st_uid)) != NULL)
	{
		g_space.user = counting_spaces(g_space.user,\
				ft_strlen(pwd->pw_name), 1);
		g_space.group = counting_spaces(g_space.group,\
				ft_strlen(grp->gr_name), 1);
	}
}

static int	adding_n(int i)
{
	if (i == 0)
	{
		if (g_flag & A)
			return (1);
		else if ((g_flag & A) == 0 && sd->d_name[0] != '.')
			return (2);
	}
	else if (i == 1)
	{
		if (g_flag & A && g_flag & R && ft_strcmp(sd->d_name, ".") != 0 &&
				ft_strcmp(sd->d_name, "..") != 0)
			return (1);
		else if ((g_flag & A) == 0 && sd->d_name[0] != '.' && g_flag & R)
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
		spaces();
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
	g_space.one = 0;
	g_space.two = 0;
	g_space.name = 0;
	g_space.group = 0;
	g_space.user = 0;
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

void		add_path(char *path, int i)
{
	char	*tmp;
	DIR		*d;
	t_lst	*d_path;

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
		add_path(d_path->content, 1);
		free(d_path->content);
		free(d_path);
		d_path = d_path->next;
	}
	closedir(d);
}
