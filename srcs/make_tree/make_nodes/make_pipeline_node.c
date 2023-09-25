/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipeline_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 05:21:22 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/24 23:20:06 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	has_pipe_operator(char **words)
{
	size_t	i;

	i = 0;
	while (words && words[i] && !is_operator(words[i]))
		i++;
	if (words && words[i] && !lp_strncmp(words[i], "|", 2))
		return (true);
	return (false);
}

t_node	*make_pipeline_node(char **words)
{
	t_node	*node;
	t_node	*tmp;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = PIPE_NODE;
	node->data = array_new(10, sizeof(t_node *), NULL, NULL);
	while (words)
	{
		tmp = make_cmd_node(words);
		if (!tmp || !array_pushback(&node->data, &tmp))
			return (NULL);
		if (!has_pipe_operator(words))
			break ;
		array_remove(words, 0);
	}
	add_to_garbage(node, GRBG_TREE_NODE);
	return (node);
}
