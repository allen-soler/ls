/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 14:43:57 by jallen            #+#    #+#             */
/*   Updated: 2019/01/19 17:29:34 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		ls_options(char *av)
{
	int		i;

	i = 0;
	while (av[i])
	{
		if (av[i] == 'l')
			g_flag |= L;
		if (av[i] == 'a')
			g_flag |= A;
		if (av[i] == 'R')
			g_flag |= R;
		if (av[i] == 't')
			g_flag |= T;
		if (av[i] == 'r')
			g_flag |= RR;
		if (av[i] == 'G')
			g_flag |= G;
		i++;
	}
}

static void	valid_av(int ac, char **av, int *i)
{
	int	j;
	int	ok;

	while (*i < ac && ft_strlen(av[*i]) >= 2 && av[*i][0] == '-')
	{
		j = 1;
		while (av[*i][j])
		{
			ok = 1;
			if (!ft_strchr("arRltG", av[*i][j]))
			{
				ok = 0;
				if (ok == 0)
				{
					ft_fprintf(2, "ls : illegaloption -- %c\
							\nusage : ls [-aGlRrt] [file ...]\n", av[*i][j]);
					exit(1);
				}
			}
			j++;
		}
		ls_options(av[*i]);
		*i = *i + 1;
	}
}

static void	multi_file(char **av, int ac, int start)
{
	char	*tmp;
	t_lst	*d_path;

	d_path = NULL;
	while (start < ac)
	{
		tmp = ft_strjoin(av[start], "/");
		if (ac >= 4)
		{
			add_path(d_path, tmp, 1);
			if (start + 1 != ac)
				ft_putchar('\n');
		}
		else
			add_path(d_path, tmp, 0);
		free_list(d_path);
		free(tmp);
		start++;
	}
}

static void	ls_type(char **av, int ac, int start)
{
	char	*tmp;
	t_lst	*d_path;

	d_path = NULL;
	tmp = NULL;
	if (ac == start)
	{
		tmp = ft_strdup("./");
		add_path(d_path, tmp, 0);
		free(tmp);
	}
	else if (start < ac)
		multi_file(av, ac, start);
}

int			main(int ac, char **av)
{
	int		start;
	t_lst	*d_path;

	d_path = NULL;
	start = 1;
	valid_av(ac, av, &start);
	if (ac == 1)
	{
		add_path(d_path, "./", 0);
		return (0);
	}
	if (ac >= 2)
		ls_type(av, ac, start);
	return (0);
}
