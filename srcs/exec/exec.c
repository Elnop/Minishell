/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 23:11:05 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/22 07:14:47 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wait_pids(t_array *pids)
{
	int		status;
	size_t	i;

	status = 0;
	i = 0;
	while (i < array_size(pids))
		waitpid(((pid_t *)pids)[i++], &status, 0);
	array_free(pids);
	return (WIFEXITED(status) & WEXITSTATUS(status));
}

int	exec(t_node *node)
{
	int		status;
	t_array	pids;

	status = 0;
	if (node->type == CMD_NODE)
		waitpid(exec_cmd(*(t_cmd_data *)node->data), &status, 0);
	if (node->type == PIPE_NODE)
	{
		pids = exec_pipe(*(t_node_links *)node->data); 
		// FAIRE UN TABLEAU DE NODES POUR LES PIPES
		return (wait_pids(pids));
	}
	return (WIFEXITED(status) & WEXITSTATUS(status));
}
