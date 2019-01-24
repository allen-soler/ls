/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 13:40:28 by jallen            #+#    #+#             */
/*   Updated: 2019/01/24 13:51:43 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		spaces_file(char *name)
{
	grp = getgrgid(f_stat.st_gid);
	g_space.one = counting_spaces(g_space.one, (int)f_stat.st_size, 0);
	g_space.two = counting_spaces(g_space.two, (int)f_stat.st_nlink, 0);
	g_space.name = counting_spaces(g_space.name, ft_strlen(name), 1);
	if ((pwd = getpwuid(f_stat.st_uid)) != NULL)
		g_space.user = counting_spaces(g_space.user,\
				ft_strlen(pwd->pw_name), 1);
	g_space.group = counting_spaces(g_space.group,\
			ft_strlen(grp->gr_name), 1);
}

void		spaces(void)
{
	grp = getgrgid(f_stat.st_gid);
	g_space.one = counting_spaces(g_space.one, (int)f_stat.st_size, 0);
	g_space.two = counting_spaces(g_space.two, (int)f_stat.st_nlink, 0);
	g_space.name = counting_spaces(g_space.name, ft_strlen(sd->d_name), 1);
	if ((pwd = getpwuid(f_stat.st_uid)) != NULL)
		g_space.user = counting_spaces(g_space.user,\
				ft_strlen(pwd->pw_name), 1);
	g_space.group = counting_spaces(g_space.group,\
			ft_strlen(grp->gr_name), 1);
}

void		init(void)
{
	g_space.one = 0;
	g_space.two = 0;
	g_space.name = 0;
	g_space.group = 0;
	g_space.user = 0;
}
