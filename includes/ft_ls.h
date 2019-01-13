/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 23:27:12 by jallen            #+#    #+#             */
/*   Updated: 2019/01/13 16:46:09 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../src/libft/libft.h"
# include "../src/ft_printf/includes/ft_printf.h"
# include <sys/types.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>
# define C_RED     "\x1b[31m"
# define C_GREEN   "\x1b[32m"
# define C_YELLOW  "\x1b[33m"
# define C_BLUE    "\x1b[96m"
# define C_MAGENTA "\x1b[35m"
# define C_CYAN    "\x1b[36m"
# define C_RESET   "\x1b[0m"

struct dirent	*sd;
struct stat		f_stat;
struct passwd	*pwd;
struct group	*grp;

typedef struct		s_lst
{
	char			*content;
	int				data;
	struct s_lst	*next;
	struct s_lst	*child;
}					t_lst;
/*
**Nodes
*/
t_lst				*new_node(char *name, int data);
t_lst				*add_sibling(t_lst *n, char *name, int data);
t_lst				*add_child(t_lst *n, char *name, int data);
void				lst_add(t_lst **head, t_lst *new);
void				ft_print(t_lst *root);
/*
**sort
*/
void				swap_list(t_lst *p1, t_lst *p2);
void				sort_ascii(t_lst *head);
void				sort_int(t_lst *head);
void				reverse_child(t_lst **head_ref);
/*
**path
*/
char				*check_path(char *path, char *o_path, int n);
void				add_path(char *path, t_lst *head, int n, int i);
/*
**printing
*/
void				ft_ls_l(char *name, struct stat fstat);
/*
**stats
*/
char				*get_time(struct stat date);
int					ft_chmod(char *rights);
void				g_link(char *path, int n);
char				*g_rights(struct stat fstat, char *rights);

#endif