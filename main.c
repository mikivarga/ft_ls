/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvarga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 16:10:57 by mvarga            #+#    #+#             */
/*   Updated: 2017/04/11 13:58:07 by mvarga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char *g_flag = "lRart";

static void		ft_save_flags(char c)
{
	if (c == 'l')
		g_l = 1;
	else if (c == 'R')
		g_big_r = 1;
	else if (c == 'a')
		g_a = 1;
	else if (c == 'r')
		g_r = 1;
	else if (c == 't')
		g_t = 1;
	else
	{
		ft_printf("ft_ls: illegal option -- %c\n", c);
		ft_printf("usage: ft_ls [-%s] [file ...]\n", g_flag);
		exit(EXIT_FAILURE);
	}
}

static void		ft_check_flags(char *name)
{
	while (*(++name))
	{
		if (*name == '-')
		{
			ft_printf("ft_ls: illegal option -- %c\n", *name);
			ft_printf("usage: ft_ls [-%s] [file ...]\n", g_flag);
			exit(EXIT_FAILURE);
		}
		else
			ft_save_flags(*name);
	}
}

static void		ft_check_type(char **name)
{
	int			type;

	type = ft_err(*name);
	if (type != -1)
	{
		if (type == S_IFDIR)
			ft_check_directory(*name);
		else if (type == S_IFLNK && !g_l)
			ft_check_directory(*name);
		else
			ft_check_file_dir_link(name);
	}
}

static void		ft_init_global_val(void)
{
	g_l = 0;
	g_big_r = 0;
	g_a = 0;
	g_r = 0;
	g_t = 0;
}

int				main(int argc, char **argv)
{
	ft_init_global_val();
	if (argc == 1)
		ft_check_directory(".");
	else
	{
		if (ft_strcmp(*(++argv), "--") == 0)
			++argv;
		while (*(*argv) == '-' && *argv)
		{
			if (ft_strcmp(*argv, "-") != 0)
				ft_check_flags(*argv);
			else
				break ;
			if (*++argv == NULL)
				break ;
		}
		if (*argv == NULL)
			ft_check_directory(".");
		else if (*(argv + 1) == NULL)
			ft_check_type(argv);
		else
			ft_check_file_dir_link(argv);
	}
	return (0);
}
