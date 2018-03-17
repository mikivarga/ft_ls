/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvarga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 11:50:35 by mvarga            #+#    #+#             */
/*   Updated: 2017/04/11 14:54:32 by mvarga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft_function/ft_printf.h"
# include "libft_function/libft/libft.h"

# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>
# include <time.h>
# include <stdio.h>

# include <unistd.h>
# include <string.h>

# define MAX_PATH 1024
# define MAXITEMS 100000
# define TRUE 1
# define FALSE 0

typedef struct dirent	t_dir;
typedef struct stat		t_stat;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

int			g_l;
int			g_big_r;
int			g_a;
int			g_r;
int			g_t;

int			g_length_nlink;
int			g_length_uid;
int			g_length_gid;
int			g_length_file;
int			g_length_major;
int			g_length_minor;
int			g_total;

char		*g_str_display;

int			g_fl;

typedef struct			s_item
{
	char				name[MAX_PATH];
	time_t				seconds;
	int					major;
	int					minor;
	int					count;
}						t_item;

typedef struct			s_trnode
{
	t_item				item;
	struct s_trnode		*left;
	struct s_trnode		*right;
}						t_trnode;

typedef struct			s_pair
{
	t_trnode			*parent;
	t_trnode			*child;
}						t_pair;

typedef struct			s_tree
{
	t_trnode			*root;
	int					size;
}						t_tree;

void					ft_initialize_tree(t_tree *ptree);
int						ft_tree_is_empty(const t_tree *ptree);
int						ft_tree_is_full(const t_tree *ptree);
int						ft_tree_item_count(const t_tree *ptree);
int						ft_to_right(const t_item *i1, const t_item *i2);
int						ft_to_left(const t_item *i1, const t_item *i2);
t_pair					ft_seek_item(const t_item *pi, const t_tree *ptree);
int						ft_add_item(const t_item *pi, t_tree *ptree);
int						ft_delete_item(t_item *pi, t_tree *ptree);
void					ft_delete_all(t_tree *ptree);
void					ft_traverse\
(int order, t_tree *ptree, void (*pfun)(t_item item, t_tree *));
void					ft_init(t_tree *ptree);
void					ft_error(t_item item, t_tree *ptree);
int						ft_err(char *name);
void					ft_err_permision(char *name);
void					ft_check_file_dir_link(char **name);
void					ft_save_file_dir_link(char *name, t_tree *ptree);
void					ft_check_directory(char *name);
void					ft_save_dirwalk(char *name, t_tree *ptree);
t_item					ft_major_minor(t_stat *st, t_item item);
void					ft_show_file(t_item item, t_tree *ptree);
void					ft_show_dir_lnk(t_item item, t_tree *ptree);
void					ft_show_files_dir(t_item item, t_tree *ptree);
void					ft_display_all(t_item item);
#endif
