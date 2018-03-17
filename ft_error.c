/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvarga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 17:58:25 by mvarga            #+#    #+#             */
/*   Updated: 2017/04/11 14:04:25 by mvarga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_error(t_item item, t_tree *ptree)
{
	t_stat		st;
	char		*begin_name;
	char		*tmp;

	tmp = item.name;
	begin_name = item.name;
	if (lstat(item.name, &st) == -1)
	{
		strerror(errno);
		while ((tmp = ft_strchr(tmp, '/')))
			begin_name = ++tmp;
		ft_printf("ft_ls: %s: ", begin_name);
		perror("");
		if (item.count > 1)
		{
			item.count--;
			ft_error(item, ptree);
		}
		ft_delete_item(&item, ptree);
	}
}

int				ft_err(char *name)
{
	int			type;
	t_stat		st;
	char		*begin_name;
	char		*tmp;

	tmp = name;
	begin_name = name;
	if (lstat(name, &st) == -1)
	{
		while ((tmp = ft_strchr(tmp, '/')))
			begin_name = ++tmp;
		ft_printf("ft_ls: %s: ", begin_name);
		perror("");
		return (-1);
	}
	type = st.st_mode & S_IFMT;
	return (type);
}

void			ft_err_permision(char *name)
{
	ft_printf("ft_ls: %s: Permision denided\n", ft_strrchr(name, '/') + 1);
	g_total = -1;
}

t_item			ft_major_minor(t_stat *st, t_item item)
{
	int		type;

	type = st->st_mode & S_IFMT;
	if (type == S_IFCHR || type == S_IFBLK)
	{
		item.major = (int)major(st->st_rdev);
		item.minor = (int)minor(st->st_rdev);
	}
	return (item);
}

void			ft_init(t_tree *ptree)
{
	g_length_nlink = 0;
	g_length_uid = 0;
	g_length_gid = 0;
	g_length_file = -1;
	g_length_major = -1;
	g_length_minor = -1;
	g_total = 0;
	ft_initialize_tree(ptree);
}
