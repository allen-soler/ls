/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:12:06 by jallen            #+#    #+#             */
/*   Updated: 2019/01/13 16:54:20 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	*get_time(struct stat date)
{
	char	*f_time;

	f_time = ft_strsub(ctime(&date.st_mtime), 4, 12);
	return (f_time);
}

void	ft_print_ls(t_lst *current)
{
	char	*tmp;

	g_link(current->content, 0);
	while (current->child)
	{
		tmp = ft_strjoin(current->content, current->child->content);
		stat(tmp, &f_stat);
		ft_ls_l(current->child->content, f_stat);
		current->child = current->child->next;
		free(tmp);
	}
	current = current->next;
	if (current != NULL)
	{
		ft_putchar('\n');
		ft_print_ls(current);
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
	if (ft_chmod(rights) / 100 == 7 && rights[0] == '-')
		printf(C_RED" %s\n"C_RESET, name);
	else if (rights[0] == 'd')
		printf(C_BLUE" %s\n"C_RESET, name);
	else
		printf(" %-5s\n", name);
	free(time);
	free(rights);
}

int		main(int ac, char **av)
{
	t_lst	*root;
	t_lst	*current;
	(void)ac;

	current = NULL;
	root = new_node(NULL, 0);
	add_path(check_path(av[1], "", 0), root, 0, 0);
	current = root->child;
	while (current)
	{
		ft_printf("%s\n", current->content);
		current = current->next;
	}
	//	ft_print_ls(current);
}
