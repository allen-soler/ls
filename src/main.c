/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 20:45:01 by jallen            #+#    #+#             */
/*   Updated: 2019/01/23 19:05:00 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		ls_options(char *av)
{
	int		i;

	i = 1;
	while (av[i])
	{
		if (av[i] == 'l' && ++i)
			g_flag |= L;
		else if (av[i] == 'a' && i++)
			g_flag |= A;
		else if (av[i] == 'R' && i++)
			g_flag |= R;
		else if (av[i] == 't' && i++)
			g_flag |= T;
		else if (av[i] == 'r' && i++)
			g_flag |= RR;
		else if (av[i] == 'G' && i++)
			g_flag |= G;
		else if (av[i] == 'f' && i++)
			g_flag |= F;
		else if (av[i] == '1' && i++)
			g_flag |= ONE;
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
			if (!ft_strchr("arRltG1f", av[*i][j]))
			{
				ok = 0;
				if (ok == 0)
				{
					ft_fprintf(2, "ls : illegal option -- %c\
							\nusage : ls [-aGlRrt1f] [file ...]\n", av[*i][j]);
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
	t_lst	*paths;

	paths = NULL;
	tmp = NULL;
	check_args(av, ac, start, &paths);
	while (paths)
	{
		tmp = check_p(paths->content, "", 0);
		add_path(tmp, 0);
		free(tmp);
		free_node(paths);
		paths = paths->next;
	}
}

static void	ls_type(char **av, int ac, int start)
{
	char	*tmp;

	tmp = NULL;
	if (ac == start)
	{
		tmp = ft_strdup("./");
		add_path(tmp, 0);
		free(tmp);
	}
	else if (start < ac)
		multi_file(av, ac, start);
}

int			main(int ac, char **av)
{
	int		start;

	start = 1;
	valid_av(ac, av, &start);
	if (ac == 1)
	{
		add_path("./", 0);
		return (0);
	}
	if (ac >= 2)
		ls_type(av, ac, start);
	return (0);
}
