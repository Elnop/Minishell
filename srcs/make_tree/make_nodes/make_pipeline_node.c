/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipeline_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 05:21:22 by lperroti          #+#    #+#             */
/*   Updated: 2023/10/10 04:00:41 by lperroti         ###   ########.fr       */
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

t_node	*subshell_cheat(char **words)
{
	t_array	buff;
	char	*tmp;
	t_node	*cmd;

	buff = array_new(3, sizeof(char *), copy_str, destroy_str);
	tmp = lp_strdup(*words + 1);
	tmp[lp_strlen(tmp) - 1] = 0;
	if (!buff)
		return (NULL);
	cmd = make_cmd_node(array_pushback_tab(&buff, (char *[3]){
				"./minishell",
				tmp,
				NULL
			}, 3));
	free(tmp);
	array_free(buff);
	array_remove(words, 0);
	return (cmd);
}

t_node	*make_pipeline_node(char **words)
{
	t_node	*node;
	t_node	*cmd;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = PIPELINE_NODE;
	node->data = array_new(10, sizeof(t_node *), NULL, NULL);
	while (words)
	{
		if (**words == '(')
			cmd = subshell_cheat(words);
		else
			cmd = make_cmd_node(words);
		if (!cmd || !array_pushback(&node->data, &cmd))
			return (array_free(node->data), free(node), NULL);
		if (!has_pipe_operator(words))
			break ;
		array_remove(words, 0);
	}
	add_grb(node, GRBG_TREE_NODE);
	return (node);
}
