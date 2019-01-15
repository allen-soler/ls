/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 10:48:15 by nalonso           #+#    #+#             */
/*   Updated: 2019/01/14 10:48:25 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	reset_buffer(t_printf *p)
{
	p->buff.current_index = 0;
	ft_memset(p->buff.str, '\0', PF_BUFF_SIZE);
}

void	write_buffer(t_printf *p)
{
	p->len += write(p->fd, p->buff.str, p->buff.current_index);
	reset_buffer(p);
}

void	buffer(t_printf *p, void *data, size_t size)
{
	int		diff;
	size_t	data_i;

	data_i = 0;
	if (!data)
		return ;
	while (PF_BUFF_SIZE - p->buff.current_index < size)
	{
		diff = PF_BUFF_SIZE - p->buff.current_index;
		ft_memcpy(&(p->buff.str[p->buff.current_index]), &(data[data_i]), diff);
		size -= diff;
		data_i += diff;
		p->buff.current_index += diff;
		write_buffer(p);
	}
	ft_memcpy(&(p->buff.str[p->buff.current_index]), &(data[data_i]), size);
	p->buff.current_index += size;
}
