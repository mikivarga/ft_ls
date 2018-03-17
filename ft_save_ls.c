/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvarga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 16:28:42 by mvarga            #+#    #+#             */
/*   Updated: 2017/04/11 13:24:33 by mvarga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		g_i;
int		g_j;

static int		ft_cnt(int tmp)
{
	int		cnt;

	cnt = 1;
	while (tmp / 10)
	{
		cnt++;
		tmp /= 10;
	}
	return (cnt);
}

static void		ft_length_part(t_stat st)
{
	t_passwd	*p;
	t_group		*g;
	int			cnt;
	int			type;

	type = st.st_mode & S_IFMT;
	p = getpwuid(st.st_uid);
	g = getgrgid(st.st_gid);
	if (g_length_uid < (cnt = (int)ft_strlen(p->pw_name)))
		g_length_uid = cnt;
	if (g_length_gid < (cnt = (int)ft_strlen(g->gr_name)))
		g_length_gid = cnt;
	if (type == S_IFCHR || type == S_IFBLK)
	{
		if (g_length_major < (cnt = ft_cnt((int)major(st.st_rdev))))
			g_length_major = cnt;
		if (g_length_minor < (cnt = ft_cnt((int)minor(st.st_rdev))))
			g_length_minor = cnt;
	}
	if (g_length_file < (cnt = ft_cnt(st.st_size)))
		g_length_file = cnt;
	if (g_length_nlink < (cnt = ft_cnt(st.st_nlink)))
		g_length_nlink = cnt;
}

void			ft_save_file_dir_link(char *name, t_tree *ptree)
{
	t_stat		st;
	t_item		item;
	int			type;

	lstat(name, &st);
	type = st.st_mode & S_IFMT;
	ft_length_part(st);
	if (type == S_IFDIR)
		ft_strcpy(item.name, name);
	else if (type == S_IFLNK && *name == '/')
		ft_strcpy(item.name, name);
	else
	{
		if (type == S_IFCHR || type == S_IFBLK)
		{
			item.major = (int)major(st.st_rdev);
			item.minor = (int)minor(st.st_rdev);
		}
		ft_strcpy(item.name, "./");
		ft_strcat(item.name, name);
	}
	ft_add_item(&item, ptree);
}

static void		ft_dirwalk(char *dir, t_dir *dp, t_tree *ptree, t_stat *st)
{
	t_item		item;
	char		name[MAX_PATH];

	ft_length_part(*st);
	if (!g_a && *dp->d_name == '.')
		return ;
	ft_strcat(ft_strcat(ft_strcpy(name, dir), "/"), dp->d_name);
	if (lstat(name, st) == -1)
	{
		ft_printf("ft_ls: %s: Permision denided\n", dp->d_name);
		g_j++;
	}
	else
	{
		ft_length_part(*st);
		ft_strcpy(item.name, name);
		g_total = g_total + (int)st->st_blocks;
		item = ft_major_minor(st, item);
		if (g_t)
			item.seconds = st->st_mtime;
		ft_add_item(&item, ptree);
	}
}

void			ft_save_dirwalk(char *name, t_tree *ptree)
{
	t_stat		st;
	t_dir		*dp;
	DIR			*dfd;

	g_i = 0;
	g_j = 0;
	lstat(name, &st);
	if ((st.st_mode & S_IFMT) == S_IFDIR || (st.st_mode & S_IFMT) == S_IFLNK)
	{
		if ((dfd = opendir(name)) == NULL)
		{
			ft_err_permision(name);
			return ;
		}
		while ((dp = readdir(dfd)) != NULL)
		{
			if (ft_strcmp(name, "/") == 0)
				*name = '\0';
			ft_dirwalk(name, dp, ptree, &st);
			g_i++;
		}
		if (g_i == g_j)
			ft_err_permision(name);
		closedir(dfd);
	}
}
