/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_add_item.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvarga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 16:35:52 by mvarga            #+#    #+#             */
/*   Updated: 2017/04/11 14:26:10 by mvarga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					ft_to_right(const t_item *i1, const t_item *i2)
{
	if (i1->seconds < i2->seconds)
		return (TRUE);
	else if ((i1->seconds == i2->seconds) && ft_strcmp(i1->name, i2->name) > 0)
		return (TRUE);
	else
		return (FALSE);
}

int					ft_to_left(const t_item *i1, const t_item *i2)
{
	if (i1->seconds > i2->seconds)
		return (TRUE);
	else if ((i1->seconds == i2->seconds) && ft_strcmp(i1->name, i2->name) < 0)
		return (TRUE);
	else
		return (FALSE);
}

static void			ft_add_node(t_trnode *new_node, t_trnode *root)
{
	if (ft_to_left(&new_node->item, &root->item))
	{
		if (root->left == NULL)
			root->left = new_node;
		else
			ft_add_node(new_node, root->left);
	}
	else if (ft_to_right(&new_node->item, &root->item))
	{
		if (root->right == NULL)
			root->right = new_node;
		else
			ft_add_node(new_node, root->right);
	}
}

static t_trnode		*ft_make_node(const t_item *pi)
{
	t_trnode	*new_node;

	new_node = (t_trnode *)malloc(sizeof(t_trnode));
	if (new_node != NULL)
	{
		new_node->item = *pi;
		new_node->item.major = -1;
		new_node->item.minor = -1;
		new_node->item.count = 1;
		new_node->left = NULL;
		new_node->right = NULL;
	}
	return (new_node);
}

int					ft_add_item(const t_item *pi, t_tree *ptree)
{
	t_trnode		*new_node;
	t_pair			seek;

	if (ft_tree_is_full(ptree))
		return (FALSE);
	if ((seek = ft_seek_item(pi, ptree)).child != NULL)
	{
		seek.child->item.count++;
		return (TRUE);
	}
	if ((new_node = ft_make_node(pi)) == NULL)
		return (FALSE);
	ptree->size++;
	if (ptree->root == NULL)
		ptree->root = new_node;
	else
		ft_add_node(new_node, ptree->root);
	return (TRUE);
}
