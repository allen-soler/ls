/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_columns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:40:55 by nalonso           #+#    #+#             */
/*   Updated: 2019/01/26 15:30:24 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int	max_length(t_lst *l)
{
	int len;
	int len1;

	len = 0;
	len1 = 0;
	if (!l)
		return (0);
	else
	{
		if (l->content)
			len = ft_strlen(l->content);
		len1 = max_length(l->next);
		return (len > len1 ? len : len1);
	}
}

static int	lst_len(t_lst *l)
{
	if (!l)
		return (0);
	else
		return (1 + lst_len(l->next));
}

void		g_colors(char *name, char *path, int width)
{
	char	*rights;
	char	*tmp;

	rights = NULL;
	tmp = ft_strjoin(path, name);
	lstat(tmp, &f_stat);
	rights = g_rights(f_stat, rights, path);
	if (ft_chmod(rights) / 100 == 7 && rights[0] == '-' && g_flag & G)
		ft_printf("{r}%-*s{R}", width, name);
	else if (rights[0] == 'd' && g_flag & G)
		ft_printf("{c}%-*s{R}", width, name);
	else if (rights[0] == 'l' && g_flag & G)
		ft_printf(C_MAGENTA"%-*s"C_RESET, width, name);
	else if (rights[0] == 's' && g_flag & G)
		ft_printf("{g}%-*s{R}", width, name);
	else if (rights[0] == 'c' && g_flag & G)
		ft_printf(C_YELLOW"{b}%-*s{R}"C_RESET, width, name);
	else
		ft_printf("%-*s", width, name);
	free(rights);
	free(tmp);
}

void		print_correct(t_lst *l, t_col s, char *path)
{
	t_lst	*tmp;

	tmp = NULL;
	if (l)
	{
		if (s.col == 0)
			tmp = get_nth_elem(l, s.row);
		else
			tmp = get_nth_elem(l, (s.row + (s.numrows * s.col)));
		if (tmp)
			g_flag & G ? g_colors(tmp->content, path, s.colwidth) :\
				ft_printf("%-*s", s.colwidth, tmp->content);
	}
}

void		print_columns(t_lst *l, char *path)
{
	t_col			s;

	s.row = 0;
	s.termwidth = 80;
	if (ioctl(1, TIOCGWINSZ, &win) == 0 && win.ws_col > 0)
		s.termwidth = win.ws_col;
	s.colwidth = max_length(l) + 1;
	s.len = lst_len(l);
	s.numcols = s.termwidth / s.colwidth;
	if (s.numcols)
		s.numrows = (s.len / s.numcols) == 0 && s.len != 0 ? 1 :\
					s.len / s.numcols + 1;
	while (s.row < s.numrows && l)
	{
		s.col = 0;
		while (s.col < s.numcols && l)
		{
			print_correct(l, s, path);
			s.col++;
		}
		ft_putchar('\n');
		s.row++;
	}
}
