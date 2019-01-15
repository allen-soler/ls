/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 11:21:36 by nalonso           #+#    #+#             */
/*   Updated: 2019/01/14 15:39:33 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int		valid_color(t_printf *p)
{
	if (*p->inp == '{')
		if (*(p->inp + 1) && ft_strchr("RBrgybmcw", *(p->inp + 1)))
			if (*(p->inp + 2) && *(p->inp + 2) == '}')
				return (1);
	return (0);
}

static char		*search_color(char cl)
{
	if (cl == 'B')
		return (BLACK);
	else if (cl == 'r')
		return (RED);
	else if (cl == 'g')
		return (GREEN);
	else if (cl == 'y')
		return (YELLOW);
	else if (cl == 'b')
		return (BLUE);
	else if (cl == 'm')
		return (MAGENTA);
	else if (cl == 'c')
		return (CYAN);
	else if (cl == 'w')
		return (WHITE);
	else
		return (RESET);
}

int				colors(t_printf *p)
{
	char	*color;

	if (valid_color(p))
	{
		++p->inp;
		color = search_color(*p->inp);
		buffer(p, color, ft_strlen(color));
		++p->inp;
		return (1);
	}
	return (0);
}
