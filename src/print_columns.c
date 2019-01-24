/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_columns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:40:55 by nalonso           #+#    #+#             */
/*   Updated: 2019/01/24 14:53:32 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			max_length(t_lst *l)
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

int			lst_len(t_lst *l)
{
	if (!l)
		return (0);
	else
		return (1 + lst_len(l->next));
}

void		print_columns(t_lst *l)
{
	struct winsize win;
	int		colwidth;
	int		termwidth;
	int		numcols;
	int		numrows;
	int		row;
	int		len;
	int		col;
	
	col = 0;
	row = 0;
	termwidth = 80;
	if (ioctl(1, TIOCGWINSZ, &win) == 0 && win.ws_col > 0)
		termwidth = win.ws_col;
	colwidth = max_length(l) + 1;
	len = lst_len(l);
	numcols = termwidth / colwidth - 1;
	numrows = (len / numcols) == 0 && len != 0 ? 1 : len / numcols;
	while (row < numrows)
	{
		while (col < numcols && l)
		{
			ft_printf("%-*s", colwidth, l->content);
			l = l->next;
			col++;
		}
		ft_putchar('\n');
		row++;
		col = 0;
	}
}
