/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 23:11:05 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/27 05:36:12 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec(t_node *node)
{
	int		status;

	status = 0;
	if (node->type == CMD_NODE)
		status = waitpid(exec_cmd((t_cmd_data *)node->data), &status, 0);
	if (node->type == PIPE_NODE)
		status = wait_pids(exec_pipeline((t_array)node->data));
	if (node->type == AND_NODE)
		status = exec_and(*(t_node_links *)node->data);
	if (node->type == OR_NODE)
		status = exec_or(*(t_node_links *)node->data);
	return (WIFEXITED(status) & WEXITSTATUS(status));
}
