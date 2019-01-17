/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 18:30:58 by jallen            #+#    #+#             */
/*   Updated: 2019/01/15 17:15:36 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static f_fl	ls_options(char *av, f_fl flags)
{
	int		i;

	i = 0;
	while (av[i])
	{
		if (av[i] == 'l')
			flags |= L;
		if (av[i] == 'a')
			flags |= A;
		if (av[i] == 'R')
			flags |= R;
		if (av[i] == 't')
			flags |= T;
		if (av[i] == 'r')
			flags |= RR;
		i++;
	}
	return (flags);
}

static void	valid_av(int ac, char **av, f_fl *flags, int *i)
{
	int	j;
	int	ok;

	ok = 1;
	while (*i < ac && ok == 1)
	{
		j = 1;
		if (av[*i][0] == '-' && ft_strlen(av[*i]) >= 2)
			while (av[*i][j])
			{
				ok = 1;
				if (av[*i][j] != 'a' && av[*i][j] != 'r' && av[*i][j] != 'R' &&
						av[*i][j] != 'l' && av[*i][j] != 't')
					ok = 0;
				if (ok == 0)
					return ;
				j++;
			}
		*flags = ls_options(av[*i], *flags); 
		*i = *i + 1; 
	}
}

void static	ls_type(char **av, f_fl flags, int ac, int start)
{
	char	*tmp;
	t_lst	*root;

	root = NULL;
	tmp = ft_strjoin(av[start], "/");
	add_path(tmp, root, flags);
	free(tmp);
}

int			main(int ac, char **av)
{
	int		start;
	t_lst	*root;
	f_fl	flag;

	start = 1;
	root = NULL;
	valid_av(ac, av, &flag, &start);
	if (ac <= 1)
	{
		add_path("./", root, flag);
		ft_print_ls(root, "./", 0);
		return (0);
	}
	if (ac >= 2)
	{
		ft_sortav(ac, av, start);
		ls_type(av, flag, ac, start);
	}
	return (0);
}
