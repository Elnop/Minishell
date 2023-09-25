/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_and_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 03:54:29 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/24 23:21:22 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_node	*make_and_node(char **words)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->data = malloc(sizeof(t_node_links));
	if (!node->data)
		return (free(node), NULL);
	node->type = AND_NODE;
	((t_node_links *)node->data)->left = make_pipeline_node(words);
	array_remove(words, 0);
	((t_node_links *)node->data)->right
		= words_to_tree(words);
	if (!((t_node_links *)node->data)->right
		|| !((t_node_links *)node->data)->left)
		return (NULL);
	add_to_garbage(node, GRBG_TREE_NODE);
	return (node);
}
