/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_l.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:12:06 by jallen            #+#    #+#             */
/*   Updated: 2019/01/19 17:32:21 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <stdio.h>

static char	*get_time(struct stat date)
{
	char	*f_time;

	f_time = ft_strsub(ctime(&date.st_mtime), 4, 12);
	return (f_time);
}

static void	ls_colors(char *name, char *buf, char *rights)
{
	if (ft_chmod(rights) / 100 == 7 && rights[0] == '-' && g_flag & G)
		ft_printf("{r}%s{R}", name);
	else if (rights[0] == 'd' && g_flag & G)
		ft_printf("{c}%s{R}", name);
	else if (rights[0] == 'l' && g_flag & G)
		ft_printf(C_MAGENTA"%s"C_RESET, name);
	else if (rights[0] == 'c' && g_flag & G)
		ft_printf(C_YELLOW"{b}%s{R}"C_RESET, name);
	else
		ft_printf("%s", name);
	if (rights[0] == 'l')
		ft_printf(" -> %s", buf);
	ft_putchar('\n');
}

static void	ft_ls_l(char *name, char *buf)
{
	char			*time;
	char			*rights;

	rights = 0;
	rights = g_rights(f_stat, rights);
	time = get_time(f_stat);
	grp = getgrgid(f_stat.st_gid);
	ft_printf("%s  ", rights);
	ft_putnchar(32, g_space.two, f_stat.st_nlink);
	ft_printf("%i ",(int)f_stat.st_nlink);
	if ((pwd = getpwuid(f_stat.st_uid)) != NULL)
		ft_printf("%s  %s", pwd->pw_name, grp->gr_name);
	if (S_ISCHR(f_stat.st_mode) || S_ISBLK(f_stat.st_mode))
		ft_printf("  %5d, %d ", (int32_t)(((f_stat.st_rdev) >> 24) & 0xff),
				(int32_t)((f_stat.st_rdev) & 0xffffff));
	else
	{
		ft_putnchar(32, g_space.one, f_stat.st_size);
		ft_printf("  %lld ", f_stat.st_size);
	}
	ft_printf("%s ", time);
	ls_colors(name, buf, rights);
	free(time);
	free(rights);
}

void		ft_normal_ls(t_lst *current, char *path)
{
	char	*rights;
	char	*tmp;

	rights = NULL;
	while (current)
	{
		tmp = ft_strjoin(path, current->content);
		lstat(tmp, &f_stat);
		rights = g_rights(f_stat, rights);
		if (ft_chmod(rights) / 100 == 7 && rights[0] == '-' && g_flag & G)
			ft_printf("{r}%s{R} ", current->content);
		else if (rights[0] == 'd' && g_flag & G)
			ft_printf("{c}%s{R} ", current->content);
		else
			ft_printf("%s ", current->content);
		current = current->next;
	}
	ft_putchar('\n');
	free(rights);
}

void		ft_print_ls(t_lst *head, char *path, int i)
{
	char	*tmp;
	char	buf[1000];

	if (g_flag & L)
	{
		ft_printf("total : %i\n", i);
		while (head)
		{
			tmp = ft_strjoin(path, head->content);
			lstat(tmp, &f_stat);
			readlink(tmp, buf, 1000);
			ft_ls_l(head->content, buf);
			head = head->next;
			free(tmp);
		}
	}
	else
		ft_normal_ls(head, path);
}
