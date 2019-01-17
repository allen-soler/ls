/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:12:06 by jallen            #+#    #+#             */
/*   Updated: 2019/01/15 18:22:31 by jallen           ###   ########.fr       */
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
	ft_printf("  %5lld %s", fstat.st_size, time);
	if (ft_chmod(rights) / 100 == 7 && rights[0] == '-')
		ft_printf(" {r}%s\n{R}", name);
	else if (rights[0] == 'd')
		ft_printf(" {c}%s\n{R}", name);
	else
		ft_printf(" %-5s ", name);
	//ft_printf("%i\n", f_stat.st_rdev);
	free(time);
	free(rights);
}

void		ft_normal_ls(t_lst *current)
{
	while (current)
	{
		ft_printf("%s ", current->child);
		current = current->next;
	}
	ft_printf("\n");
}

void		ft_print_ls(t_lst *head, char *path,  int i)
{
	char	*tmp;

	tmp = check_p(path, "", 1);
	if (i == 0)
		ft_printf("total :%i\n", i);
	else
		ft_printf("%s: \ntotal : %i\n", tmp, i);
   free(tmp);	
	while (head)
	{
		tmp = ft_strjoin(path, head->content);
		lstat(tmp, &f_stat);
		ft_ls_l(head->content, f_stat);
		head = head->next;
		free(tmp);
	}
}
/*void		ft_print_ls(t_lst *current, int i)
{
	char	*tmp;

	tmp = check_p(current->content, "", 1);
	if (i == 0)
		ft_printf("total :%i\n", current->data);
	else
		ft_printf("%s: \ntotal : %i\n", tmp, current->data);
   free(tmp);	
	while (current->child)
	{
		tmp = ft_strjoin(current->content, current->child->content);
		lstat(tmp, &f_stat);
		ft_ls_l(current->child->content, f_stat);
		current->child = current->child->next;
		free(tmp);
	}
	current = current->next;
	if (current != NULL)
	{
		ft_putchar('\n');
		ft_print_ls(current, 1);
	}
}*/
