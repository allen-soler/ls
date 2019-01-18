/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 14:43:57 by jallen            #+#    #+#             */
/*   Updated: 2019/01/18 15:29:13 by jallen           ###   ########.fr       */
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

void static multi_file(char **av, f_fl flags, int ac, int start)
{
	char	*tmp;
	t_lst	*d_path;

	d_path = NULL;
	while (start < ac)
	{
		tmp = ft_strjoin(av[start], "/");
		if (ac >= 4)
		{	
			add_path(d_path, tmp, flags, 1);
			if (start + 1 != ac)
				ft_putchar('\n');
		}
		else
			add_path(d_path, tmp, flags, 0);
		free_list(d_path);
		free(tmp);
		start++;
	}
}

void static	ls_type(char **av, f_fl flags, int ac, int start)
{
	char	*tmp;
	t_lst	*d_path;

	d_path = NULL;
	tmp = NULL;
	if (ac == start)
	{
		tmp = ft_strdup("./");
		add_path(d_path, tmp, flags, 0);
		free(tmp);
	}
	else if (start < ac)
		multi_file(av, flags, ac, start);
}

int			main(int ac, char **av)
{
	int		start;
	f_fl	flag;
	t_lst	*d_path;

	d_path = NULL;
	start = 1;
	valid_av(ac, av, &flag, &start);
	if (ac <= 1)
	{
		add_path(d_path, "./", flag, 0);
		return (0);
	}
	if (ac >= 2)
		ls_type(av, flag, ac, start);
	return (0);
}
