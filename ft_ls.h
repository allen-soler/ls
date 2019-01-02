/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 23:27:12 by jallen            #+#    #+#             */
/*   Updated: 2018/12/12 23:27:57 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <sys/types.h>
# include <dirent.h>
# include <stdio.h> /*d*/
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
struct stat	f_stat;
struct passwd	*pwd;
struct group	*grp;

typedef struct		s_lst
{
	char			*content;
	int				data;
	struct s_lst	*next;
	struct s_lst	*child;
}					t_lst;

void	ft_print(t_lst *root);
void	lst_add(t_lst **head, t_lst *new);
void	ft_print(t_lst *root);
t_lst	*new_node(char *name, int data);
t_lst	*add_sibling(t_lst *n, char *name, int data);
t_lst	*add_child(t_lst *n, char *name, int data);
void	lst_add(t_lst **head, t_lst *new);

char	*check_path(char *path, char *o_path, int n);
void	g_link(char *path, int n);
int	ft_chmod(char *rights);
char	*g_rights(struct stat file_stat, char *rights);
void	swap(t_lst *p1, t_lst *p2);
void	sort_ascii(t_lst *head);

void	ft_ls_l(char *name, struct stat fstat);
char	*get_time(struct stat date);

#endif
