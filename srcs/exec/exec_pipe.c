/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:22:18 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/22 07:15:24 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_array	*exec_pipe(t_node_links node_links)
{
	t_array	pids;
	t_array	next_pipe_pids;

	pids = array_new(10, sizeof(pid_t), NULL, NULL);
	if (node_links.left->type == CMD_NODE)
		array_pushback(&pids,
			(pid_t []){exec_cmd(*(t_cmd_data *)node_links.left->data)});
	if (node_links.right->type == CMD_NODE)
		array_pushback(&pids,
			(pid_t []){exec_cmd(*(t_cmd_data *)node_links.right->data)});
	if (node_links.right->type == PIPE_NODE)
	{
		next_pipe_pids = exec_pipe(*(t_node_links *)node_links.right->data);
		array_pushback_tab(&pids, next_pipe_pids, array_size(next_pipe_pids));
		array_free(next_pipe_pids);
	}
	return (pids);
}
