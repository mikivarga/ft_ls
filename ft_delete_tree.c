/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvarga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 17:38:43 by mvarga            #+#    #+#             */
/*   Updated: 2017/04/11 15:22:00 by mvarga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_pair			ft_seek_item(const t_item *pi, const t_tree *ptree)
{
	t_pair		look;

	look.parent = NULL;
	look.child = ptree->root;
	if (look.child == NULL)
		return (look);
	while (look.child != NULL)
	{
		if (ft_to_left(pi, &(look.child->item)))
		{
			look.parent = look.child;
			look.child = look.child->left;
		}
		else if (ft_to_right(pi, &(look.child->item)))
		{
			look.parent = look.child;
			look.child = look.child->right;
		}
		else
			break ;
	}
	return (look);
}

static void		ft_delete_node(t_trnode **ptr)
{
	t_trnode	*tmp;

	if ((*ptr)->left == NULL)
	{
		tmp = *ptr;
		*ptr = (*ptr)->right;
		free(tmp);
	}
	else if ((*ptr)->right == NULL)
	{
		tmp = *ptr;
		*ptr = (*ptr)->left;
		free(tmp);
	}
	else
	{
		tmp = (*ptr)->left;
		while (tmp->right != NULL)
			tmp = tmp->right;
		tmp->right = (*ptr)->right;
		tmp = *ptr;
		*ptr = (*ptr)->left;
		free(tmp);
	}
}

int				ft_delete_item(t_item *pi, t_tree *ptree)
{
	t_pair	look;

	look = ft_seek_item(pi, ptree);
	if (look.child == NULL)
		return (FALSE);
	if (look.child->item.count > 0)
		look.child->item.count--;
	if (look.parent == NULL)
		ft_delete_node(&ptree->root);
	else if (look.parent->left == look.child)
		ft_delete_node(&look.parent->left);
	else
		ft_delete_node(&look.parent->right);
	ptree->size--;
	return (TRUE);
}

static void		ft_delete_all_nodes(t_trnode *root)
{
	t_trnode	*pright;

	if (root != NULL)
	{
		pright = root->right;
		ft_delete_all_nodes(root->left);
		free(root);
		ft_delete_all_nodes(pright);
	}
}

void			ft_delete_all(t_tree *ptree)
{
	if (ptree != NULL)
		ft_delete_all_nodes(ptree->root);
	ptree->root = NULL;
	ptree->size = 0;
}
