/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_or_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 04:09:12 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/22 03:12:39 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_node	*make_or_node(char **words)
{
	t_node	*node;
	size_t	left_len;

	left_len = get_left_length(words, (char *)"||");
	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->data = malloc(sizeof(t_node_links));
	if (!node->data)
		return (free(node), NULL);
	node->type = OR_NODE;
	((t_node_links *)node->data)->left = make_pipeline_nodes(words); // replace by pipeline
	((t_node_links *)node->data)->right
		= words_to_tree(words + left_len + 1);
	if (!((t_node_links *)node->data)->right || !((t_node_links *)node->data)->left)
		return (NULL);
	return (node);
}
