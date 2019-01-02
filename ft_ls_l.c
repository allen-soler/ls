/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:12:06 by jallen            #+#    #+#             */
/*   Updated: 2018/12/16 22:37:02 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_time(struct stat date)
{
	char	*f_time;

	f_time = ft_strsub(ctime(&date.st_mtime), 4, 12);
	return (f_time);
}

void	show_dir_content(char *path)
{
	char			*d_path;
	DIR				*dir;
	char			*tmp;

	dir = opendir(path);
	if (dir == NULL)
		return ;
	g_link(path, 0);
	while ((sd = readdir(dir)) != NULL)
	{
		tmp = ft_strjoin(path, sd->d_name);
		stat(tmp, &f_stat);
		if (sd->d_name[0] != '.')
			ft_ls_l(sd->d_name, f_stat);
		if (sd->d_type == DT_DIR && sd->d_name[0] != '.')
			d_path = check_path(sd->d_name, path, 0);
		free(tmp);
	}
	closedir(dir);
	if (readdir(dir) == NULL && d_path != NULL)
	{
		printf("%s\n", check_path(d_path, path, 1));
		show_dir_content(d_path);
	}
}

void	ft_ls_l(char *name, struct stat fstat)
{
	char			*rights;
	char			*time;

	rights = 0;
	rights = g_rights(fstat, rights);
	time = get_time(fstat);
	grp = getgrgid(fstat.st_gid);
	printf("%s%4i ", rights, (int)fstat.st_nlink);
	if ((pwd = getpwuid(fstat.st_uid)) != NULL)
		printf("%s  %s", pwd->pw_name, grp->gr_name);
	printf("  %5lli %s", fstat.st_size, time);
	if (ft_chmod(rights) / 100 == 7 && rights[0] != 'd')
		printf(C_RED" %s\n"C_RESET, name);
	else if (rights[0] == 'd')
		printf(C_BLUE" %s\n"C_RESET, name);
	else
		printf(" %-5s\n", name);
	free(time);
	free(rights);
}
