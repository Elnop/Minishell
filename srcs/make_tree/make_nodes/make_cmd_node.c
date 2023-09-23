/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 03:52:22 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/23 07:57:43 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_array	get_cmd_args(char **words)
{
	t_array	buff;
	size_t	i;

	if (!words)
		return (NULL);
	buff = array_new(10, sizeof(char **), copy_str, destroy_str);
	i = 0;
	while (words[i] && !is_operator(words[i]))
	{
		array_pushback(&buff, words + i);
		i++;
	}
	array_pushback(&buff, NULL);
	return (buff);
}

t_node	*make_cmd_node(char **words)
{
	t_node	*node;

	if (!words || !*words)
		return (NULL);
	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->data = malloc(sizeof(t_cmd_data));
	if (!node->data)
		return (free(node), NULL);
	node->type = CMD_NODE;
	((t_cmd_data *)node->data)->fd_in = -1;
	((t_cmd_data *)node->data)->fd_out = -1;
	((t_cmd_data *)node->data)->close_fd = -1;
	((t_cmd_data *)node->data)->args = get_cmd_args(words);
	if (!((t_cmd_data *)node->data)->args)
		return (free(node->data), free(node), NULL);
	add_to_garbage(node, GRBG_TREE_NODE);
	return (node);
}
