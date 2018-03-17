/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_show.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvarga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 12:41:42 by mvarga            #+#    #+#             */
/*   Updated: 2017/04/11 14:19:08 by mvarga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_show_file(t_item item, t_tree *ptree)
{
	t_stat		st;
	int			type;

	lstat(item.name, &st);
	type = st.st_mode & S_IFMT;
	if (type == S_IFLNK && !g_l)
		return ;
	if (type == S_IFLNK && g_l)
	{
		ft_display_all(item);
		while (item.count-- > 1)
			ft_display_all(item);
		ft_delete_item(&item, ptree);
	}
	else if (type != S_IFDIR)
	{
		ft_display_all(item);
		while (item.count-- > 1)
			ft_display_all(item);
		ft_delete_item(&item, ptree);
	}
}

void			ft_show_dir_lnk(t_item item, t_tree *ptree)
{
	t_stat		st;
	int			type;
	char		tmp[MAX_PATH];

	ft_strcpy(tmp, item.name);
	lstat(item.name, &st);
	type = st.st_mode & S_IFMT;
	if (type == S_IFLNK || type == S_IFDIR)
	{
		if ((!g_big_r && g_fl) || (g_big_r && g_fl))
		{
			g_fl = 0;
			ft_printf("%s:\n", item.name);
		}
		else
			ft_printf("\n%s:\n", item.name);
		ft_check_directory(item.name);
		while (item.count-- > 1)
		{
			ft_printf("\n%s:\n", tmp);
			ft_check_directory(tmp);
		}
		ft_delete_item(&item, ptree);
	}
}

void			ft_show_files_dir(t_item item, t_tree *ptree)
{
	int			type;
	t_stat		st;
	char		*tmp;
	char		*b_n;

	b_n = item.name;
	tmp = item.name;
	lstat(item.name, &st);
	type = st.st_mode & S_IFMT;
	while ((tmp = ft_strchr(tmp, '/')))
		b_n = ++tmp;
	ft_display_all(item);
	if (!g_r)
	{
		if (type != S_IFDIR || !g_big_r)
			ft_delete_item(&item, ptree);
		else if (ft_strcmp(b_n, ".") == 0 || ft_strcmp(b_n, "..") == 0)
			ft_delete_item(&item, ptree);
	}
}
