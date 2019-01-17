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
		if (av[*i][0] == '-')
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
/*
int	main(int ac, char **av)
{
	int i = 1;
	int	j;
	f_fl	flag;
	
	valid_av(ac, av, &flag, &i);
	printf("l = %i\na = %i\nR = %i\nr = %i\nt = %i\n",flag & L, flag & A, flag & R, flag & RR, flag & T );
	return (0);
}*/
