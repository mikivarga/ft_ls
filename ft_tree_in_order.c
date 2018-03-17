/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_in_order.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvarga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 18:42:45 by mvarga            #+#    #+#             */
/*   Updated: 2017/04/11 15:19:05 by mvarga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_in_order_reverse(t_tree *pt, t_trnode *root,\
									void (*pfun)(t_item item, t_tree *))
{
	if (root != NULL)
	{
		ft_in_order_reverse(pt, root->right, pfun);
		(*pfun)(root->item, pt);
		ft_in_order_reverse(pt, root->left, pfun);
	}
}

static void		ft_in_order(t_tree *pt, t_trnode *root,\
							void (*pfun)(t_item item, t_tree *))
{
	if (root != NULL)
	{
		ft_in_order(pt, root->left, pfun);
		(*pfun)(root->item, pt);
		ft_in_order(pt, root->right, pfun);
	}
}

void			ft_traverse(int order, t_tree *ptree,\
							void (*pfun)(t_item item, t_tree *))
{
	if (ptree != NULL)
	{
		if (order)
			ft_in_order(ptree, ptree->root, pfun);
		else
			ft_in_order_reverse(ptree, ptree->root, pfun);
	}
}
