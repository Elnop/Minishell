/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elnop <elnop@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:22:18 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/30 15:19:45 by elnop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_node	*get_cmd(t_node *node)
{
	while (node && node->type != CMD_NODE)
		node = ((t_redir_data *)node->data)->next;
	return (node);
}

t_array	exec_pipeline(t_array nodes)
{
	t_array		pids;
	int			pipe_fds[2];
	size_t		i;
	t_node		*p_cmd_node;

	pids = array_new(10, sizeof(pid_t), NULL, NULL);
	i = 0;
	while (i < array_size(nodes))
	{
		p_cmd_node = get_cmd(((t_node **)nodes)[i]);
		if (!pipe_cmds(p_cmd_node, pipe_fds, i, array_size(nodes)))
			return (NULL);
		if (!open_redirs(((t_node **)nodes)[i], p_cmd_node))
			return (NULL);
		if (!p_cmd_node && ++i)
			continue ;
		array_pushback(&pids,
			(pid_t []){exec_cmd(((t_cmd_data *)p_cmd_node->data))});
		if (p_cmd_node && ((t_cmd_data *)p_cmd_node->data)->fd_in > -1)
			close(((t_cmd_data *)p_cmd_node->data)->fd_in);
		i++;
	}
	return (pids);
}
