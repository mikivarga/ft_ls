/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvarga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 16:21:14 by mvarga            #+#    #+#             */
/*   Updated: 2017/04/11 14:04:37 by mvarga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_save_global_str(int val, char *flag)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_itoa(val);
	tmp2 = ft_strjoin(g_str_display, tmp1);
	free(g_str_display);
	free(tmp1);
	g_str_display = ft_strjoin(tmp2, flag);
	free(tmp2);
}

static void		ft_change_len_for_display(void)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_itoa(g_length_nlink);
	tmp2 = ft_strjoin("%", tmp1);
	free(tmp1);
	g_str_display = ft_strjoin(tmp2, "d %-");
	free(tmp2);
	ft_save_global_str(g_length_uid, "s  %-");
	ft_save_global_str(g_length_gid, "s  %");
}

void			ft_check_file_dir_link(char **name)
{
	t_tree		tree;
	int			cnt_d;
	int			cnt_f_d;

	g_fl = 1;
	ft_init(&tree);
	while (*name)
		ft_save_file_dir_link(*name++, &tree);
	ft_traverse(1, &tree, ft_error);
	ft_change_len_for_display();
	cnt_f_d = ft_tree_item_count(&tree);
	ft_traverse(g_r ? 0 : 1, &tree, ft_show_file);
	cnt_d = ft_tree_item_count(&tree);
	if ((cnt_d > 0 && cnt_f_d > cnt_d))
		ft_printf("\n");
	if (g_str_display)
		free(g_str_display);
	ft_traverse(g_r ? 0 : 1, &tree, ft_show_dir_lnk);
}

static void		ft_delete_files_dir(t_item item, t_tree *ptree)
{
	int		type;
	t_stat	st;
	char	*tmp;
	char	*b_n;

	b_n = item.name;
	tmp = item.name;
	lstat(item.name, &st);
	type = st.st_mode & S_IFMT;
	while ((tmp = ft_strchr(tmp, '/')))
		b_n = ++tmp;
	if (type != S_IFDIR || !g_big_r)
		ft_delete_item(&item, ptree);
	else if (ft_strcmp(b_n, ".") == 0 || ft_strcmp(b_n, "..") == 0)
		ft_delete_item(&item, ptree);
}

void			ft_check_directory(char *name)
{
	t_tree		tree;

	ft_init(&tree);
	ft_save_dirwalk(name, &tree);
	ft_traverse(1, &tree, ft_error);
	if (g_l && g_total >= 0)
		ft_printf("total %d\n", g_total);
	ft_change_len_for_display();
	ft_traverse(g_r ? 0 : 1, &tree, ft_show_files_dir);
	if (g_r)
		ft_traverse(g_r ? 0 : 1, &tree, ft_delete_files_dir);
	if (g_str_display)
		free(g_str_display);
	ft_traverse(g_r ? 0 : 1, &tree, ft_show_dir_lnk);
}
