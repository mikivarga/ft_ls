/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvarga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 16:31:08 by mvarga            #+#    #+#             */
/*   Updated: 2017/04/11 15:21:37 by mvarga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_initialize_tree(t_tree *ptree)
{
	ptree->root = NULL;
	ptree->size = 0;
}

int					ft_tree_is_empty(const t_tree *ptree)
{
	if (ptree->root == NULL)
		return (TRUE);
	else
		return (FALSE);
}

int					ft_tree_is_full(const t_tree *ptree)
{
	if (ptree->size == MAXITEMS)
		return (TRUE);
	else
		return (FALSE);
}

int					ft_tree_item_count(const t_tree *ptree)
{
	return (ptree->size);
}
