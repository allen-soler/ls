/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 23:27:12 by jallen            #+#    #+#             */
/*   Updated: 2019/01/24 16:55:36 by jallen           ###   ########.fr       */
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
# include <sys/acl.h>
# include <sys/xattr.h>
# include <sys/ioctl.h>
# define C_RED     "\x1b[31m"
# define C_GREEN   "\x1b[32m"
# define C_YELLOW  "\x1b[43m"
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
# define F (1 << 6)
# define ONE (1 << 7)

struct dirent	*sd;
struct stat		f_stat;
struct passwd	*pwd;
struct group	*grp;
struct winsize	win;

typedef struct		s_lst
{
	char			*content;
	long			data;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_sp
{
	int				one;
	int				two;
	int				name;
	int				user;
	int				group;
}					t_sp;

typedef struct		s_col
{
	int				colwidth;
	int				termwidth;
	int				numcols;
	int				numrows;
	int				len;
	int				row;
	int				col;
}					t_col;

typedef short		t_fl;

t_fl	g_flag;
t_sp	g_space;

/*
**Nodes + nodes tools
*/
t_lst				*new_node(char *name, int data);
void				lst_add(t_lst **head, t_lst *new);
void				ft_print(t_lst *root);
void				free_list(t_lst *head);
void				free_node(t_lst *head);
/*
**sort
*/
void				swap_list(t_lst *p1, t_lst *p2);
void				reverse_child(t_lst **head_ref);
void				ft_sortav(int ac, char **av, int start);
void				merge_sort(t_lst **h, int func);
void				sorting(t_lst **current, t_lst **d_path);
/*
**path
*/
char				*check_p(char *path, char *o_path, int n);
void				add_path(char *path, int i);
/*
**printing
*/
void				ft_print_ls(t_lst *head, char *path, int i);
void				printing_files(t_lst *path, t_lst *folders);
void				ft_ls_l(char *name, char *buf, char *path);
void				print_columns(t_lst *l, char *path);
void				ls_colors(char *name, char *buf, char *rights, int i);
int					num_len(int nb);
/*
**stats
*/
int					ft_chmod(char *rights);
char				*g_rights(struct stat fstat, char *rights, char *path);
/*
** spaces + misc
*/
int					counting_spaces(int spaces, int max, int len);
int					n_sp(int max, int min, int len);
void				spaces(void);
void				spaces_file(char *name);
void				init(void);
/*
** multi file
*/
void				check_args(char **a, int ac, int start, t_lst **paths);

#endif
