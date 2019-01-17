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

static t_flag	ls_options(int ac, char **av, int *i)
{
	int		j;
	t_fl		flags;

	while (*i < ac)
	{
		j = 1;
		if (valid_av(av[*i]) == 1)
			while (av[*i][j])
			{
				if (av[*i][j] == 'l')
					flags.l |= L;
				if (av[*i][j] == 'a')
					flags.a |= A;
				if (av[*i][j] == 'R')
					flags.Re |= R;
				if (av[*i][j] == 't')
					flags.t |= T;
				if (av[*i][j] == 'r')
					flags.r |= RR;
				j++;
			}
		else
			break ;
		*i = *i + 1;
	}
}


int	main(int ac, char **av)
{
	int i = atoi(av[1]);
	char r = 0;

	//ft_test(av[1]);
	if (i == 0)
		r &= ~L;
	else
		r |= L;
	printf("%i\n", r);
	return (0);
}
