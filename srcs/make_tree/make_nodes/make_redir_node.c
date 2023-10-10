/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redir_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 04:44:31 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/10 04:00:41 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_redir_data	*make_redir_data(char **words, size_t i)
{
	t_redir_data	*redir_data;

	redir_data = malloc(sizeof(t_redir_data));
	if (!redir_data)
		return (NULL);
	redir_data->file_name = words[i + 1];
	if (!lp_strncmp(words[i], "<", 2))
		redir_data->type = REDIR_IN;
	else if (!lp_strncmp(words[i], ">", 2))
		redir_data->type = REDIR_OUT;
	else if (!lp_strncmp(words[i], ">>", 3))
		redir_data->type = REDIR_OUT_APPEND;
	redir_data->file_name = lp_strdup(words[i + 1]);
	array_remove((t_array)words, i);
	array_remove((t_array)words, i);
	redir_data->next = make_cmd_node(words);
	return (redir_data);
}

t_node	*make_redir_node(char **words)
{
	t_node	*p_node;
	size_t	i;

	i = 0;
	while (words[i] && !is_operator(words[i]))
		i++;
	if (is_redir_operator(words[i])
		&& (!words[i + 1] || is_operator(words[i + 1])))
		return (NULL);
	p_node = malloc(sizeof(t_node));
	p_node->type = REDIR_NODE;
	p_node->data = make_redir_data(words, i);
	if (!p_node->data)
		return (free(p_node), NULL);
	add_grb(p_node, GRBG_TREE_NODE);
	return (p_node);
}
