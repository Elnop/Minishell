/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 03:52:22 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/05 18:25:33 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_array	get_cmd_args(char **words)
{
	t_array	buff;

	if (!words || !*words)
		return (NULL);
	buff = array_new(10, sizeof(char *), copy_str, destroy_str);
	while (*words && !is_operator(*words))
	{
		array_pushback(&buff, words);
		array_remove((t_array)words, 0);
	}
	array_pushback(&buff, NULL);
	return (buff);
}

bool	set_cmd_data(t_cmd_data *cmd_data, char **words)
{
	cmd_data->fd_in = -1;
	cmd_data->fd_out = -1;
	cmd_data->close_fd = -1;
	cmd_data->args = get_cmd_args(words);
	if (!cmd_data->args)
		return (false);
	return (true);
}

t_node	*make_cmd_node(char **words)
{
	t_node	*node;

	if (words && *words && has_redir_operator(words))
		return (make_redir_node(words));
	if (words && *words && has_heredoc_operator(words))
		return (make_heredoc_node(words));
	if (!words || !*words || is_operator(*words))
		return (NULL);
	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->data = malloc(sizeof(t_cmd_data));
	if (!node->data)
		return (free(node), NULL);
	node->type = CMD_NODE;
	if (!set_cmd_data((t_cmd_data *)node->data, words))
		return (free((t_cmd_data *)node->data), free(node), NULL);
	add_to_garbage(node, GRBG_TREE_NODE);
	return (node);
}
