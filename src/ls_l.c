/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:12:06 by jallen            #+#    #+#             */
/*   Updated: 2019/01/18 15:19:03 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static char	*get_time(struct stat date)
{
	char	*f_time;

	f_time = ft_strsub(ctime(&date.st_mtime), 4, 12);
	return (f_time);
}

static void	ft_ls_l(char *name, struct stat fstat)
{
	char			*rights;
	char			*time;

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
	ft_printf("%s", time);
	if (ft_chmod(rights) / 100 == 7 && rights[0] == '-')
		ft_printf(" {r}%s\n{R}", name);
	else if (rights[0] == 'd')
		ft_printf(" {c}%s\n{R}", name);
	else
		ft_printf(" %-5s\n", name);
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
		if (ft_chmod(rights) / 100 == 7 && rights[0] == '-')
			ft_printf(" {r}%s{R}", current->content);
		else if (rights[0] == 'd')
			ft_printf(" {c}%s{R}", current->content);
		else
			ft_printf("%s ", current->content);
		current = current->next;
	}
	ft_putchar('\n');
}

void		ft_print_ls(t_lst *head, char *path, int i, f_fl flag)
{
	char	*tmp;

	if (flag & L)
	{
		ft_printf("total : %i\n", i);
		while (head)
		{
			tmp = ft_strjoin(path, head->content);
			lstat(tmp, &f_stat);
			ft_ls_l(head->content, f_stat);
			head = head->next;
			free(tmp);
		}
	}
	else
		ft_normal_ls(head, path);
}
