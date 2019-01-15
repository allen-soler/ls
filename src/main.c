/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 18:30:58 by jallen            #+#    #+#             */
/*   Updated: 2019/01/15 16:04:29 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int	valid_av(char *av)
{
	int	i;
	int	ok;

	i = 1;
	ok = 0;
	if (av[0] == '-')
		while (av[i])
		{
			ok = 1;
			if (av[i] != 'a' && av[i] != 'r' && av[i] != 'R' &&
					av[i] != 'l' && av[i] != 't')
				ok = 0;
			if (ok == 0)
				return (ok);
			i++;
		}
	return (ok);
}

static void	ls_options(int ac, char **av, char *flags, int *i)
{
	int		j;

	while (*i < ac)
	{
		j = 1;
		if (valid_av(av[*i]) == 1)
			while (av[*i][j])
			{
				if (av[*i][j] == 'l')
					flags[0] = '1';
				if (av[*i][j] == 'a')
					flags[1] = '2';
				if (av[*i][j] == 'R')
					flags[2] = '3';
				if (av[*i][j] == 't')
					flags[3] = '4';
				if (av[*i][j] == 'r')
					flags[4] = '5';
				j++;
			}
		else
			break ;
		*i = *i + 1;
	}
}

void static	ls_type(char **av, char *flags, int ac, int start)
{
	char	*tmp;
	t_lst	*root;

	root = NULL;
	if (ft_atoi(flags) == 10000 || ft_atoi(flags) == 2000 || ft_atoi(flags) == 300
			|| ft_atoi(flags) == 40 || ft_atoi(flags) == 5)
		return ;
	tmp = start == ac ?  ft_strdup("./") : ft_strjoin(av[start], "/");
	add_path(tmp, root, flags);
	free(tmp);
}

int			main(int ac, char **av)
{
	char	*flags;
	int		start;
	t_lst	*root;

	start = 1;
	root = NULL;
	flags = ft_strdup("00000");
	ls_options(ac, av, flags, &start);
	if (ac <= 1)
	{
		add_path("./", root, flags);
		ft_print_ls(root, "./", 0);
		free(flags);
		return (0);
	}
	if (ac >= 2)
	{
		ft_sortav(ac, av, start);
		ls_type(av, flags, ac, start);
		free(flags);
	}
	return (0);
}
