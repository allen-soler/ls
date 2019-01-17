/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 18:30:58 by jallen            #+#    #+#             */
/*   Updated: 2019/01/17 20:38:49 by jallen           ###   ########.fr       */
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
	while (*i < ac && ft_strlen(av[*i]) >= 2 && av[*i][0] == '-')
	{
		j = 1;
		while (av[*i][j])
		{
			ok = 1;
			if (av[*i][j] != 'a' && av[*i][j] != 'r' && av[*i][j] != 'R'
					&& av[*i][j] != 'l' && av[*i][j] != 't')
				ok = 0;
			j++;
		}
		*flags = ls_options(av[*i], *flags);
		if (ok == 0)
			return ;	   
		*i = *i + 1; 
	}
}

void static	ls_type(char **av, f_fl flags, int ac, int start)
{
	char	*tmp;

	if (ac == start)
	{
		tmp = ft_strdup("./");
		add_path(tmp, flags);
		free(tmp);
	}
	else if (start < ac)
	{
		while (start < ac)
		{
			tmp = ft_strjoin(av[start], "/");
			add_path(tmp, flags);
			free(tmp);
			start++;
		}
	}
}

int			main(int ac, char **av)
{
	int		start;
	f_fl	flag;

	start = 1;
	valid_av(ac, av, &flag, &start);
	if (ac <= 1)
	{
		add_path("./", flag);
		return (0);
	}
	if (ac >= 2)
		ls_type(av, flag, ac, start);
	return (0);
}
