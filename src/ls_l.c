/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:12:06 by jallen            #+#    #+#             */
/*   Updated: 2019/01/18 18:47:09 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static char	*get_time(struct stat date)
{
	char	*f_time;

	f_time = ft_strsub(ctime(&date.st_mtime), 4, 12);
	return (f_time);
}

static void	ls_colors(char *name, char *buf, f_fl flag, char *rights)
{
	if (ft_chmod(rights) / 100 == 7 && rights[0] == '-' && flag & G)
		ft_printf("{r}%s{R}", name);
	else if (rights[0] == 'd' && flag & G)
		ft_printf(" {c}%s{R}", name);
	else if (rights[0] == 'l' && flag & G)
		ft_printf(C_MAGENTA" %s"C_RESET, name);
	else if (rights[0] == 'c' && flag & G)
		ft_printf(C_YELLOW"{b}%s{R}"C_RESET, name);
	else
		ft_printf("%s", name);
	if (rights[0] == 'l')
		ft_printf(" -> %s", buf);
	ft_putchar('\n');
}

static void	ft_ls_l(char *name, struct stat fstat, f_fl flag, char *buf)
{
	char			*time;
	char			*rights;

	rights = 0;
	rights = g_rights(fstat, rights);
	time = get_time(fstat);
	grp = getgrgid(fstat.st_gid);
	ft_printf("%s%4i ", rights, (int)fstat.st_nlink);
	if ((pwd = getpwuid(fstat.st_uid)) != NULL)
		ft_printf("%s  %s", pwd->pw_name, grp->gr_name);
	if (S_ISCHR(fstat.st_mode) || S_ISBLK(fstat.st_mode))
		ft_printf("  %5d, %d ", (int32_t)(((fstat.st_rdev) >> 24) & 0xff),
				(int32_t)((fstat.st_rdev) & 0xffffff));
	else
		ft_printf("  %5lld ", fstat.st_size);
	ft_printf("%s ", time);
	ls_colors(name, buf, flag, rights);
	free(time);
	free(rights);
}

void		ft_normal_ls(t_lst *current, char *path, f_fl flag)
{
	char	*rights;
	char	*tmp;

	rights = NULL;
	while (current)
	{
		tmp = ft_strjoin(path, current->content);
		lstat(tmp, &f_stat);
		rights = g_rights(f_stat, rights);
		if (ft_chmod(rights) / 100 == 7 && rights[0] == '-' && flag & G)
			ft_printf("{r}%s{R} ", current->content);
		else if (rights[0] == 'd' && flag & G)
			ft_printf("{c}%s{R} ", current->content);
		else
			ft_printf("%s ", current->content);
		current = current->next;
	}
	ft_putchar('\n');
	free(rights);
}

void		ft_print_ls(t_lst *head, char *path, int i, f_fl flag)
{
	char	*tmp;
	char	buf[1000];

	if (flag & L)
	{
		ft_printf("total : %i\n", i);
		while (head)
		{
			tmp = ft_strjoin(path, head->content);
			lstat(tmp, &f_stat);
			readlink(tmp, buf, 1000);
			ft_ls_l(head->content, f_stat, flag, buf);
			head = head->next;
			free(tmp);
		}
	}
	else
		ft_normal_ls(head, path, flag);
}
