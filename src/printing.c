/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:07:02 by jallen            #+#    #+#             */
/*   Updated: 2019/01/26 15:34:46 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <stdio.h>

static size_t	compute_time(struct tm *l)
{
	size_t	ret;

	ret = ((l->tm_year * 365) * 24 * 3600);
	ret += (l->tm_mon * 30 * 24) * 3600;
	ret += (l->tm_mday) * 24 * 3600;
	ret += (l->tm_hour) * 3600;
	ret += (l->tm_min) * 60;
	return (ret);
}

static void		get_time(struct stat date)
{
	char		*f_time;
	struct tm	*foo;
	struct tm	*foo1;
	time_t		rawtime;

	f_time = NULL;
	time(&rawtime);
	foo = localtime(&rawtime);
	foo1 = gmtime(&(date.st_mtime));
	if (compute_time(foo) - compute_time(foo1) > 15552000)
	{
		f_time = ft_strsub(ctime(&date.st_mtime), 4, 6);
		ft_printf("%s  ", f_time);
		free(f_time);
		f_time = ft_strdup(&ctime(&date.st_mtime)[20]);
		f_time[ft_strlen(f_time) - 1] = '\0';
		ft_printf("%s ", f_time);
	}
	else
	{
		f_time = ft_strsub(ctime(&date.st_mtime), 4, 12);
		ft_printf("%s ", f_time);
	}
	free(f_time);
}

void			ls_colors(char *name, char *buf, char *rights, int i)
{
	if (ft_chmod(rights) / 100 == 7 && rights[0] == '-' && g_flag & G)
		ft_printf("{r}%s{R}", name);
	else if (rights[0] == 'd' && g_flag & G)
		ft_printf("{c}%s{R}", name);
	else if (rights[0] == 'l' && g_flag & G)
		ft_printf(C_MAGENTA"%s"C_RESET, name);
	else if (rights[0] == 'c' && g_flag & G)
		ft_printf(C_YELLOW"{b}%s{R}"C_RESET, name);
	else if (rights[0] == 's' && g_flag & G)
		ft_printf("{g}%s{R}", name);
	else
		ft_printf("%s", name);
	if (rights[0] == 'l')
		ft_printf(" -> %s", buf);
	if (i == 1)
		ft_putchar('\n');
}

void			ft_ls_l(char *name, char *buf, char *path)
{
	char		*rights;

	rights = 0;
	rights = g_rights(f_stat, rights, path);
	grp = getgrgid(f_stat.st_gid);
	ft_printf("%s ", rights);
	ft_printf("%*d ", g_space.two, (int)f_stat.st_nlink);
	if ((pwd = getpwuid(f_stat.st_uid)))
		ft_printf("%-*s%-*s", g_space.user + 2, pwd->pw_name,\
				g_space.group, grp->gr_name);
	else
		ft_printf("      %*-s", g_space.group, grp->gr_name);
	if (S_ISCHR(f_stat.st_mode) || S_ISBLK(f_stat.st_mode))
		ft_printf("  %5d, %d ", (int32_t)(((f_stat.st_rdev) >> 24) & 0xff),
				(int32_t)((f_stat.st_rdev) & 0xffffff));
	else
		ft_printf("%*d ", g_space.one + 2, (int)f_stat.st_size);
	get_time(f_stat);
	ls_colors(name, buf, rights, 1);
	free(rights);
}

void			ft_print_ls(t_lst *head, char *path, int i)
{
	char	*tmp;
	char	buf[1000];

	ft_bzero(buf, 1000);
	if (g_flag & ONE)
		print_one(head, path);
	else if (g_flag & L && (ONE & g_flag) == 0)
	{
		if (head)
			ft_printf("total %i\n", i);
		while (head)
		{
			tmp = ft_strjoin(path, head->content);
			lstat(tmp, &f_stat);
			readlink(tmp, buf, 1000);
			ft_ls_l(head->content, buf, tmp);
			head = head->next;
			free(tmp);
		}
	}
	else
		print_columns(head, path);
}
