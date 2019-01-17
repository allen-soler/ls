/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 22:19:00 by jallen            #+#    #+#             */
/*   Updated: 2019/01/15 18:25:05 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	free_list(t_lst *head)
{
	t_lst	*tmp;

	while(head)
	{
		tmp = head;
		head = head->next;
		free(tmp->content);
		free(tmp);
	}
}
static void	sorting(t_lst **current, t_lst **d_path, f_fl flag)
{
	if (current != NULL)
	{
		if ((flag & T) == 0)
			sort_ascii(*current);
		if ((flag & T) == 4)
			sort_int(*current);
		if ((flag & RR)  == 5)
			reverse_child(current);
	}
	if (d_path)
	{
		if ((flag & T) == 0)
			sort_ascii(*d_path);
		if ((flag & T) == 4)
			sort_int(*d_path);
		if ((flag & RR) == 5)
			reverse_child(d_path);
	}
}

void	add_path(char *path, t_lst *head, f_fl flag)
{
	t_lst			*d_path;
	DIR				*d;
	char			*tmp;
	time_t			time;
	int				i;

	d_path = NULL;
	head = NULL;
	i = 0;
	if (!(d = opendir(path)))
	{
		ft_printf("test");
		path = check_p(path, "", 1);
		ft_printf("ls: %s: %s\n", path, strerror(errno));
		free(path);
		return ;
	}
	while ((sd = readdir(d)) != NULL)
	{
		time = 0;
		tmp = ft_strjoin(path, sd->d_name);
		lstat(tmp, &f_stat);
		if (f_stat.st_mode > time)
			time = f_stat.st_mtime;
		if (sd->d_name[0] != '.')
			i = i + f_stat.st_blocks;
		if (sd->d_name[0] != '.' && (flag & A) == 0)
			lst_add(&head, new_node(sd->d_name, (long)time));	
		if (sd->d_type == DT_DIR && sd->d_name[0] != '.' && (flag & A) == 0 && (flag & R) != 0)
			lst_add(&d_path, new_node(check_p(sd->d_name, path, 0), (long)time));
		if (sd->d_name[0] && (flag & A) != 0)
			lst_add(&head, new_node(sd->d_name, (long)time));	
		if (sd->d_type == DT_DIR && ft_strcmp(sd->d_name,".")  != 0 && 
				ft_strcmp(sd->d_name, "..") != 0 && (flag & A) != 0 && (flag & R) != 0)
			lst_add(&d_path, new_node(check_p(sd->d_name, path, 0), (long)time));
		free(tmp);
	}
	sorting(&head, &d_path, flag);
	ft_print_ls(head, path, i);
	free_list(head);
	while (d_path)
	{
		ft_putchar('\n');
		add_path(d_path->content, head, flag);
		free(d_path->content);
		d_path = d_path->next;
	}
	closedir(d);
}
