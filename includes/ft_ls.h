/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 23:27:12 by jallen            #+#    #+#             */
/*   Updated: 2019/01/19 16:30:42 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libftprintf/includes/ft_printf.h"
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
# define C_YELLOW  "\x1b[43m"
# define C_BLUE    "\x1b[96m"
# define C_MAGENTA "\x1b[35m"
# define C_CYAN    "\x1b[36m"
# define C_RESET   "\x1b[0m"

/*
**Flags
*/
# define L (1 << 0)
# define A (1 << 1)
# define R (1 << 2)
# define RR (1 << 3)
# define T (1 << 4)
# define G (1 << 5)

struct dirent	*sd;
struct stat		f_stat;
struct passwd	*pwd;
struct group	*grp;

typedef struct		s_lst
{
	char			*content;
	long			data;
	struct s_lst	*next;
	struct s_lst	*child;
}					t_lst;

typedef struct		s_sp
{
	int				one;
	int				two;
}					t_sp;

typedef short		t_fl;

t_fl	g_flag;
t_sp	g_space;

/*
**Nodes
*/
t_lst				*new_node(char *name, int data);
void				lst_add(t_lst **head, t_lst *new);
void				ft_print(t_lst *root);
void				free_list(t_lst *head);
/*
**sort
*/
void				swap_list(t_lst *p1, t_lst *p2);
void				sort_ascii(t_lst *head);
void				sort_int(t_lst *head);
void				reverse_child(t_lst **head_ref);
void				ft_sortav(int ac, char **av, int start);
/*
**path
*/
char				*check_p(char *path, char *o_path, int n);
void				add_path(t_lst *d_path, char *path, int i);
/*
**printing
*/
void				ft_normal_ls(t_lst *current, char *path);
void				ft_print_ls(t_lst *head, char *path, int i);
/*
**stats
*/
int					ft_chmod(char *rights);
char				*g_rights(struct stat fstat, char *rights);
/*
** spaces + misc
*/
int					counting_spaces(int spaces, int max);
void				ft_putnchar(char c, int max, int min);

#endif
