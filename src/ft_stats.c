/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stats.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 14:15:40 by jallen            #+#    #+#             */
/*   Updated: 2019/01/13 22:52:52 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char		*check_p(char *path, char *o_path, int n)
{
	int		i;
	char	*r;

	i = ft_strlen(path);
	r = NULL;
	if (path[i - 1] != '/' && n == 0)
	{
		r = ft_strjoin(path, "/");
		r = ft_strjoin(o_path, r);
		return (r);
	}
	if (path[i - 1] == '/' && n == 1)
	{
		r = ft_strdup(path);
		r[i - 1] = '\0';
		return (r);
	}
	return (path);
}

void		g_link(char *path, int n)
{
	DIR				*dir;
	int				i;
	char			*tmp;

	i = 0;
	if ((dir = opendir(path)) == NULL)
		exit(1);
	while ((sd = readdir(dir)) != NULL)
	{
		tmp = ft_strjoin(path, sd->d_name);
		stat(tmp, &f_stat);
		if (sd->d_name[0] != '.' && n == 0)
			i = i + f_stat.st_blocks;
		if (n > 0)
			i = i + f_stat.st_blocks;
		free(tmp);
	}
	closedir(dir);
	(n == 0 ? printf("%s: total %i\n", path, i) :
	printf("%s: total %i\n", path, i));
}

int			ft_chmod(char *rights)
{
	int	i;
	int	n_mod;

	i = 1;
	n_mod = 0;
	while (rights[i])
	{
		if (rights[i] == 'x')
			n_mod = 1 + n_mod;
		if (rights[i] == 'w')
			n_mod = 2 + n_mod;
		if (rights[i] == 'r')
			n_mod = n_mod + 4;
		i++;
		if (i == 4 || i == 7)
			n_mod = n_mod * 10;
	}
	return (n_mod);
}

static void	file_type(char *rights, struct stat fstat)
{
	if (S_ISREG(fstat.st_mode))
		rights[0] = '-';
	else if (S_ISDIR(fstat.st_mode))
		rights[0] = 'd';
	else if (S_ISLNK(fstat.st_mode))
		rights[0] = 'l';
	else if (S_ISBLK(fstat.st_mode))
		rights[0] = 'b';
	else if (S_ISCHR(fstat.st_mode))
		rights[0] = 'c';
	else if (S_ISSOCK(fstat.st_mode))
		rights[0] = 's';
	else if (S_ISFIFO(fstat.st_mode))
		rights[0] = 'p';
	else
		rights[0] = '-';
}

char		*g_rights(struct stat fstat, char *rights)
{
	if (!(rights = malloc(sizeof(char) * 11)))
		return (0);
	file_type(rights, fstat);
	rights[1] = *((fstat.st_mode & S_IRUSR) ? "r" : "-");
	rights[2] = *((fstat.st_mode & S_IWUSR) ? "w" : "-");
	rights[3] = *((fstat.st_mode & S_IXUSR) ? "x" : "-");
	rights[4] = *((fstat.st_mode & S_IRGRP) ? "r" : "-");
	rights[5] = *((fstat.st_mode & S_IWGRP) ? "w" : "-");
	rights[6] = *((fstat.st_mode & S_IXGRP) ? "x" : "-");
	rights[7] = *((fstat.st_mode & S_IROTH) ? "r" : "-");
	rights[8] = *((fstat.st_mode & S_IWOTH) ? "w" : "-");
	rights[9] = *((fstat.st_mode & S_IXOTH) ? "x" : "-");
	rights[10] = '\0';
	return (rights);
}
