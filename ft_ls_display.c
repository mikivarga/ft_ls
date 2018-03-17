/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvarga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 19:34:41 by mvarga            #+#    #+#             */
/*   Updated: 2017/04/11 14:15:48 by mvarga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			ft_display_permisions(int type)
{
	if (S_ISDIR(type))
		ft_printf("d");
	else if (S_ISLNK(type))
		ft_printf("l");
	else if (S_ISCHR(type))
		ft_printf("c");
	else if (S_ISBLK(type))
		ft_printf("b");
	else
		ft_printf("-");
	ft_printf("%c%c%c%c%c%c%c%c%c  ",
			(type & S_IRUSR) ? 'r' : '-',
			(type & S_IWUSR) ? 'w' : '-',
			(type & S_IXUSR) ? 'x' : '-',
			(type & S_IRGRP) ? 'r' : '-',
			(type & S_IWGRP) ? 'w' : '-',
			(type & S_IXGRP) ? 'x' : '-',
			(type & S_IROTH) ? 'r' : '-',
			(type & S_IWOTH) ? 'w' : '-',
			(type & S_IXOTH) ? 'x' : '-');
}

static void			ft_display_fname_lnk(t_item item)
{
	char		*tmp;
	char		*name;
	char		lnk_tmp[MAX_PATH];
	int			linklen;
	t_stat		st;

	lstat(item.name, &st);
	linklen = 0;
	name = item.name;
	tmp = item.name;
	while ((tmp = ft_strchr(tmp, '/')))
		name = ++tmp;
	ft_printf("%s", name);
	if ((st.st_mode & S_IFMT) == S_IFLNK)
	{
		ft_printf(" -> ");
		linklen = readlink(item.name, lnk_tmp, sizeof(lnk_tmp));
		lnk_tmp[linklen] = '\0';
		ft_printf("%s", lnk_tmp);
	}
}

static int			ft_display_major_minor(t_stat *pst)
{
	char		*tmp1;
	char		*tmp2;
	char		*tmp3;
	int			type;

	type = pst->st_mode & S_IFMT;
	if (type == S_IFCHR || type == S_IFBLK)
	{
		tmp1 = ft_itoa(g_length_major);
		tmp2 = ft_strjoin(" %", tmp1);
		free(tmp1);
		tmp1 = ft_strjoin(tmp2, "d, %");
		free(tmp2);
		tmp2 = ft_itoa(g_length_minor);
		tmp3 = ft_strjoin(tmp1, tmp2);
		free(tmp2);
		tmp2 = ft_strjoin(tmp3, "d");
		free(tmp3);
		ft_printf(tmp2, (int)major(pst->st_rdev), (int)minor(pst->st_rdev));
		free(tmp2);
		free(tmp1);
		return (TRUE);
	}
	return (FALSE);
}

static void			ft_display_size_file(t_stat *pst)
{
	char		*tmp1;
	char		*tmp2;

	if (g_length_major != -1 && g_length_minor != -1)
	{
		tmp1 = ft_itoa(g_length_major + g_length_minor);
		tmp2 = ft_strjoin("   %", tmp1);
	}
	else
	{
		tmp1 = ft_itoa(g_length_file);
		tmp2 = ft_strjoin("%", tmp1);
	}
	free(tmp1);
	tmp1 = ft_strjoin(tmp2, "lld");
	free(tmp2);
	ft_printf(tmp1, pst->st_size);
	free(tmp1);
}

void				ft_display_all(t_item item)
{
	t_passwd	*p;
	t_group		*g;
	time_t		t;
	t_stat		st;
	char		tmp[MAX_PATH];

	lstat(item.name, &st);
	t = time(NULL);
	ft_strncpy(tmp, (ctime(&t) + 20), 6);
	if (g_l)
	{
		p = getpwuid(st.st_uid);
		g = getgrgid(st.st_gid);
		ft_display_permisions(st.st_mode);
		ft_printf(g_str_display, st.st_nlink, p->pw_name, g->gr_name);
		if (!ft_display_major_minor(&st))
			ft_display_size_file(&st);
		ft_printf(" %.6s ", ctime(&st.st_mtime) + 4);
		if (ft_strcmp(tmp, ctime(&st.st_mtime) + 20) == 0)
			ft_printf("%.5s ", ctime(&st.st_mtime) + 11);
		else
			ft_printf(" %.4s ", ctime(&st.st_mtime) + 20);
	}
	ft_display_fname_lnk(item);
	ft_printf("\n");
}
